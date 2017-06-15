#include "texture_manager.h"

#include <rapidxml.hpp>
#include "../../util/fileutils.h"

namespace zeta {
	namespace graphics {

		TextureManager* TextureManager::inst;

		TextureManager::TextureManager() {
			inst = this;
			
			unsigned int page = 0;
			while (util::fileExists("../res/textures/page" + std::to_string(page) + ".xml")) {
				genPage(page);
				++page;
			}
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

				double x_normal = (double)atoi(child->first_attribute("x")->value());
				double x = x_normal / width;
				double y_normal = (double)atoi(child->first_attribute("y")->value());
				double y = y_normal / height;
				double w_normal = (double)atoi(child->first_attribute("w")->value());
				double w = w_normal / width;
				double h_normal = (double)atoi(child->first_attribute("h")->value());
				double h = h_normal / height;

				double px_normal = atof(child->first_attribute("pX")->value());
				double py_normal = atof(child->first_attribute("pY")->value());
				
				data.size = { w_normal, h_normal };
#if ZETA_TEXTURE_MANAGER_SET_PIVOT_TO_ORIGIN
				data.pivot = { 0, 0 };
#else
				data.pivot = { px_normal * w_normal, py_normal * h_normal };
#endif

				data.uvStart = glm::vec2(x, 1-(y+h));
				data.uvEnd = glm::vec2(x+w, 1-y);

				m_textures.emplace(std::string(child->first_attribute("n")->value()), data);
			}
		}
	}
}