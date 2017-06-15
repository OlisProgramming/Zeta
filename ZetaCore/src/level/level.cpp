#include "level.h"

#include <rapidxml.hpp>
#include <rapidxml_print.hpp>
#include "../util/fileutils.h"

namespace zeta {
	namespace level {

		Level::Level(const std::string& tmxFileName) {

			using namespace rapidxml;

			std::string fname = "../res/maps/" + tmxFileName;
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
					tilesetData.tex = new Texture(textureSource);
					tilesetData.tileWidth = atoi(tilesetNode->first_attribute("tilewidth")->value());
					tilesetData.tileHeight = atoi(tilesetNode->first_attribute("tileheight")->value());
					tilesetData.columns = atoi(tilesetNode->first_attribute("columns")->value());
					tilesetData.rows = atoi(tilesetNode->first_attribute("tilecount")->value()) / tilesetData.columns;
					tilesetData.firstgid = atoi(firstgid.c_str());

					m_tilesets.push_back(tilesetData);
				}

				else if (std::string(child->name()) == "layer") {
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

										m_tiles.push_back(new Sprite({ x, y, 0 }, { tilesetData.tileWidth, tilesetData.tileHeight }, m_tilesets[tilesetIndex].tex, uvstart, uvend, false));
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
			}
		}

		Level::~Level() {
			for (Entity* ent : m_entities) {
				delete ent;
			}
		}
	}
}