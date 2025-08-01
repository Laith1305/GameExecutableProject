#pragma once
#include "Font.h"
#include "Renderer/Renderer (2).h"
#include "Vector3.h"
#include <memory>

struct SDL_Texture;

namespace viper {
	class Text {
	public:
		Text() = default;
		Text(std::shared_ptr<class Font> font) : font{ font } {}
		~Text();

		bool Create(Renderer& renderer, const std::string& text, const vec3& color);
		void Draw(Renderer& renderer, float x, float y);

	private:
		std::shared_ptr<class Font> font{ nullptr };
		SDL_Texture* texture{ nullptr };
	};
}