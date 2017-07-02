#include "level.h"

#include <rapidxml.hpp>
#include <rapidxml_print.hpp>
#include "../util/fileutils.h"
#include "../util/logging.h"
#include "../entity/behaviour_factory.h"
#include "../graphics/texture/tileset_manager.h"

namespace zeta {
	namespace level {

		using namespace graphics;
		using namespace entity;

		Level::Level(const std::string& tmxFileName) {

			using namespace rapidxml;

			ZLog("Loading level " + tmxFileName + " into memory");

			std::string fname = "../res/maps/" + tmxFileName + ".tmx";
			std::string text = util::readFileText(fname.c_str());
			xml_document<> doc;
			doc.parse<0>(&text[0]);

			// Must cast to string otherwise it does not compare equal
			if (std::string(doc.first_node()->name()) != "map") {
				printf("Level generation failed for file %s: first node was not a map node! Got: %s\n", fname.c_str(), doc.first_node()->name());
				return;
			}
			xml_node<>* root = doc.first_node();

			for (xml_node<>* child = root->first_node(); child; child = child->next_sibling()) {
				if (std::string(child->name()) == "tileset") {
					std::string firstgid = child->first_attribute("firstgid")->value();
					std::string source = "../res/maps/" + std::string(child->first_attribute("source")->value());
					ZLog("Loading level's tileset data (" + source + ")");
					
					std::string tilesetText = util::readFileText(source.c_str());
					xml_document<> tilesetDoc;
					tilesetDoc.parse<0>(&tilesetText[0]);

					if (std::string(tilesetDoc.first_node()->name()) != "tileset") {
						printf("Level generation failed for file %s: first node was not a map node! Got: %s\n", fname.c_str(), tilesetDoc.first_node()->name());
						return;
					}
					xml_node<>* tilesetNode = tilesetDoc.first_node();
					xml_node<>* imageNode = tilesetNode->first_node();
					std::string textureSource = "../res/tilesets/" + std::string(imageNode->first_attribute("source")->value());

					TilesetData tilesetData;
					tilesetData.tex = TilesetManager::inst->get(textureSource);
					tilesetData.tileWidth = atoi(tilesetNode->first_attribute("tilewidth")->value());
					tilesetData.tileHeight = atoi(tilesetNode->first_attribute("tileheight")->value());
					tilesetData.columns = atoi(tilesetNode->first_attribute("columns")->value());
					tilesetData.rows = atoi(tilesetNode->first_attribute("tilecount")->value()) / tilesetData.columns;
					tilesetData.firstgid = atoi(firstgid.c_str());
					
					m_tilesets.push_back(tilesetData);

					tilesetDoc.clear();
				}

				else if (std::string(child->name()) == "layer") {
					ZLog("Loading level's tile data");
					for (xml_node<>* layerChild = child->first_node(); layerChild; layerChild = layerChild->next_sibling()) {

						if (std::string(layerChild->name()) == "data") {
							// Use the CSV format to decode the tile data.
							std::string data = layerChild->value();

							std::string currentStr;
							unsigned int x = 0;
							unsigned int y = 0;
							for (unsigned int ind = data.find_first_of('\n')+1; ind < data.length(); ++ind) {
								if (data[ind] == ',') {
									unsigned int id = atoi(currentStr.c_str());
									currentStr.clear();
									if (id != 0) {
										unsigned int tilesetIndex = m_tilesets.size() - 1;

										for (unsigned int i = 0; i < m_tilesets.size(); ++i) {
											if (id < m_tilesets[i].firstgid) {
												tilesetIndex = i - 1;
											}
										}

										TilesetData& tilesetData = m_tilesets[tilesetIndex];
										float individualTileUvWidth = 1.f / (float)tilesetData.columns;
										float individualTileUvHeight = 1.f / (float)tilesetData.rows;
										unsigned int gid = id - tilesetData.firstgid;
										unsigned int uvX = gid % tilesetData.columns;
										unsigned int uvY = gid / tilesetData.rows;
										glm::vec2 uvstart((float)uvX * individualTileUvWidth, 1 - (float)(uvY+1) * individualTileUvHeight);
										glm::vec2 uvend(uvstart.x + individualTileUvWidth, uvstart.y + individualTileUvHeight);
										
										//printf("%d,%d to %d,%d\n", x, y, x + tilesetData.tileWidth, y + tilesetData.tileHeight);

										m_tiles.push_back(Sprite({ x, y, -100000 }, { tilesetData.tileWidth, tilesetData.tileHeight }, m_tilesets[tilesetIndex].tex, uvstart, uvend, false));
									}
									x += 32;
								}
								else if (data[ind] == '\n') {
									y += 32;
									x = 0;
								}
								else {
									currentStr.push_back(data[ind]);
								}
							}

							// By this point, the full CSV has been read.
						}
					}
				}

				else if (std::string(child->name()) == "objectgroup") {
					ZLog("Loading level's object data");
					for (xml_node<>* objectNode = child->first_node(); objectNode; objectNode = objectNode->next_sibling()) {
						int x = atoi(objectNode->first_attribute("x")->value());
						int y = atoi(objectNode->first_attribute("y")->value());
						int w = atoi(objectNode->first_attribute("width")->value());
						int h = atoi(objectNode->first_attribute("height")->value());
						xml_node<>* propertiesNode = objectNode->first_node("properties");
						if (!propertiesNode) continue;  // abort creation of entity
						Entity* ent = new Entity({ x, y, 0 }, { w, h });
						for (xml_node<>* propertyNode = propertiesNode->first_node(); propertyNode; propertyNode = propertyNode->next_sibling()) {
							std::string propClassName = propertyNode->first_attribute("name")->value();
							std::string propParams = propertyNode->first_attribute("value")->value();
							if (propClassName == "Collision") {
								if (propParams == "aabb") {
									ent->setPhysObj(new physics::AABB(glm::vec2(ent->getPos()), glm::vec2(ent->getPos()) + ent->getSize()));
								}
								else {
									printf("Invalid collision type on level generation! Got %s, expected 'aabb'.\n", propParams.c_str());
								}
							}
							else if (propClassName == "Solid") {
								if (util::isTruthy(propParams)) {
									ent->setSolid(true);
								}
								else {
									ent->setSolid(false);
								}
							}
							else {
								ent->addBehaviour(BehaviourFactory::inst->generate(propClassName, ent, propParams));
							}
						}
						addEntity(ent);
					}
				}
			}

			doc.clear();

			ZLog("Finished loading level");
		}

		Level::~Level() {
			for (Entity* ent : m_entities) {
				ent->preDestroy();
			}
			for (Entity* ent : m_entities) {
				ent->destroy();
			}
			for (Entity* ent : m_entities) {
				ent->postDestroy();
			}
			for (Entity* ent : m_entities) {
				delete ent;
			}
		}
	}
}