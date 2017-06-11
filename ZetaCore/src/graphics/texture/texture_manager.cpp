#include "texture_manager.h"

#include <rapidxml.hpp>
#include "../../util/fileutils.h"

namespace zeta {
	namespace graphics {

		TextureManager* TextureManager::inst;

		TextureManager::TextureManager() {
			inst = this;
			
			genPage(0);
		}

		TextureManager::~TextureManager() {
			for (Texture* page : m_pages) {
				delete page;
			}
		}

		void TextureManager::genPage(unsigned int page) {

			Texture* tpage = new Texture("../res/textures/page" + std::to_string(page) + ".png");
			m_pages.push_back(tpage);

			using namespace rapidxml;

			std::string fname = "../res/textures/page" + std::to_string(page) + ".xml";
			std::string text = util::readFileText(fname.c_str());
			xml_document<> doc;
			doc.parse<0>(&text[0]);

			// Must cast to string otherwise it does not compare equal
			if (std::string(doc.first_node()->name()) != "TextureAtlas") {
				printf("Texture generation failed for file %s: first node was not a TextureAtlas! Got: %s\n", fname.c_str(), doc.first_node()->name());
				return;
			}
			xml_node<>* root = doc.first_node();

			double width = (double)atoi(root->first_attribute("width")->value());
			double height = (double)atoi(root->first_attribute("height")->value());

			for (xml_node<>* child = root->first_node(); child; child = child->next_sibling())
			{
				TextureData data;
				data.page = page;

				double x = (double)atoi(child->first_attribute("x")->value()) / width;
				double y = (double)atoi(child->first_attribute("y")->value()) / height;
				double w = (double)atoi(child->first_attribute("w")->value()) / width;
				double h = (double)atoi(child->first_attribute("h")->value()) / height;
				
				data.uvStart = glm::vec2(x, 1-(y+h));
				data.uvEnd = glm::vec2(x+w, 1-y);

				m_textures.emplace(std::string(child->first_attribute("n")->value()), data);
			}
		}
	}
}