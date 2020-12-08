#pragma once
#include <glew.h>
#include "Vertex.h"
#include <glm\glm.hpp>
#include <vector>

namespace NTCrystal{

	class RenderBatch
	{
	public:

		RenderBatch(GLuint Offset, GLuint NumVertecies, GLuint Texture) : m_offset(Offset), m_numVertecies(NumVertecies), m_texture(Texture){}

		GLuint m_offset;
		GLuint m_numVertecies;
		GLuint m_texture;
	};

	//Sorting for glyph array
	enum class GlyphSortType
	{
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE 
	};

	//Stores texture data
	class Glyph{

	public:

		Glyph(){};

		Glyph(const glm::vec4 &DestRect, const glm::vec4 &UVRect, 
			GLuint Texture, float Depth, const ColorRGBA8 &Color);

		Glyph(const glm::vec4 &DestRect, const glm::vec4 &UVRect, 
			GLuint Texture, float Depth, const ColorRGBA8 &Color, float angle);


		//this is stored after glBindTexture when we get texture id
		GLuint m_texture;
		float m_depth;

		Vertex m_topLeft;
		Vertex m_bottomLeft;
		Vertex m_topRight;
		Vertex m_bottomRight;
	private:
		glm::vec2 rotatePoint(glm::vec2 position, float angle);		
	};

	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();


		void init();

		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
		void end();

		void draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, 
			GLuint texture, float depth, const ColorRGBA8 &color);

		void draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, 
			GLuint texture, float depth, const ColorRGBA8 &color, float angle);

		void draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, 
			GLuint texture, float depth, const ColorRGBA8 &color, const glm::vec2 &direction);

		void renderBatch();

	private:
		void createRenderBatches();

		void createVertexArray();

		void sortGlyphs();

		static bool compareFrontToBack(Glyph *a, Glyph *b);
		static bool compareBackToFront(Glyph *a, Glyph *b);
		static bool compareTexture(Glyph *a, Glyph *b);


		GLuint m_vbo;
		GLuint m_vao;

		GlyphSortType m_sortType;

		//Pointers for sorting glyph array
		std::vector<Glyph*> m_glyphsPointers;
		std::vector<Glyph> m_glyphs;

		std::vector<RenderBatch> m_renderBatches;

	};
}

