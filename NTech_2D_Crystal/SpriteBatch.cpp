#include "SpriteBatch.h"
#include <algorithm>

namespace NTCrystal{

	SpriteBatch::SpriteBatch() : m_vbo(0), m_vao(0)
	{
	}


	SpriteBatch::~SpriteBatch()
	{
	}

	void SpriteBatch::init()
	{
		createVertexArray();
	}

	//this will setup for begin rendering
	void SpriteBatch::begin(GlyphSortType sortType) //its set to texture by default
	{
		m_sortType = sortType;
		m_renderBatches.clear();

		m_glyphs.clear();
	}

	void SpriteBatch::end()
	{
		m_glyphsPointers.resize(m_glyphs.size());
		//stup all ponters for fast sorting
		for (int i = 0; i < m_glyphs.size(); i++){
			m_glyphsPointers[i] = &m_glyphs[i];
		}

		sortGlyphs();
		createRenderBatches();
	}

	void SpriteBatch::draw(const glm::vec4 &destRect, const glm::vec4 &uvRect,
		GLuint texture, float depth, const ColorRGBA8 &color)
	{
		m_glyphs.emplace_back(destRect, uvRect, texture, depth, color);
	}

	void SpriteBatch::draw(const glm::vec4 &destRect,
		const glm::vec4 &uvRect, GLuint texture, float depth, const ColorRGBA8 &color, float angle)
	{
		m_glyphs.emplace_back(destRect, uvRect, texture, depth, color, angle);
	}

	void SpriteBatch::draw(const glm::vec4 &destRect, const glm::vec4 &uvRect,
		GLuint texture, float depth, const ColorRGBA8 &color, const glm::vec2 &direction)
	{
		//origin
		const glm::vec2 right(1.0f, 0.0f);

		float angle = std::acos(glm::dot(right, direction));

		if (direction.y < 0.0f)
			angle = -angle;


		m_glyphs.emplace_back(destRect, uvRect, texture, depth, color, angle);
	}

	void SpriteBatch::renderBatch()
	{
		glBindVertexArray(m_vao);

		for (int i = 0; i < m_renderBatches.size(); i++)
		{
			glBindTexture(GL_TEXTURE_2D, m_renderBatches[i].m_texture);

			glDrawArrays(GL_TRIANGLES, m_renderBatches[i].m_offset, m_renderBatches[i].m_numVertecies);
		}

		glBindVertexArray(0);
	}

	void SpriteBatch::createRenderBatches()
	{
		std::vector <Vertex> vertices;

		vertices.resize(m_glyphsPointers.size() * 6); //this will optimize 

		if (m_glyphsPointers.empty())
		{
			return;
		}

		int offset = 0;
		int cv = 0; //current vertex

		m_renderBatches.emplace_back(0, 6, m_glyphsPointers[0]->m_texture); //this will create render batch type faster

		vertices[cv++] = m_glyphsPointers[0]->m_topLeft;
		vertices[cv++] = m_glyphsPointers[0]->m_bottomLeft;
		vertices[cv++] = m_glyphsPointers[0]->m_bottomRight;
		vertices[cv++] = m_glyphsPointers[0]->m_bottomRight;
		vertices[cv++] = m_glyphsPointers[0]->m_topRight;
		vertices[cv++] = m_glyphsPointers[0]->m_topLeft;
		offset += 6;


		for (int cg = 1; cg < m_glyphsPointers.size(); cg++)
		{
			if (m_glyphsPointers[cg]->m_texture != m_glyphsPointers[cg - 1]->m_texture)
			{
				m_renderBatches.emplace_back(offset, 6, m_glyphsPointers[cg]->m_texture); //this will create render batch type faster
			}
			else
			{
				m_renderBatches.back().m_numVertecies += 6;
			}

			vertices[cv++] = m_glyphsPointers[cg]->m_topLeft;
			vertices[cv++] = m_glyphsPointers[cg]->m_bottomLeft;
			vertices[cv++] = m_glyphsPointers[cg]->m_bottomRight;
			vertices[cv++] = m_glyphsPointers[cg]->m_bottomRight;
			vertices[cv++] = m_glyphsPointers[cg]->m_topRight;
			vertices[cv++] = m_glyphsPointers[cg]->m_topLeft;
			offset += 6;
		}

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		//orphan the buffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		//upload data
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

	void SpriteBatch::createVertexArray()
	{
		//Vertex array is array that encapsulates all vetesies for current sprite
		if (m_vao == 0){
			glGenVertexArrays(1, &m_vao);
		}

		glBindVertexArray(m_vao);

		if (m_vbo == 0){
			glGenBuffers(1, &m_vbo);
		}
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		//NOTE pass some difretent shader

		//Tell opengl that we want to use the first
		//attribute array. We only need one array right
		//now since we are only using position.
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//This is the position attribute pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		//This is the color attribute pointer
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		//This is the UV attribute pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		glBindVertexArray(0);
	}

	void SpriteBatch::sortGlyphs()
	{
		switch (m_sortType)
		{
		case NTCrystal::GlyphSortType::NONE:
			break;
		case NTCrystal::GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(m_glyphsPointers.begin(), m_glyphsPointers.end(), compareFrontToBack); //third is comparator
			break;
		case NTCrystal::GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(m_glyphsPointers.begin(), m_glyphsPointers.end(), compareBackToFront);
			break;
		case NTCrystal::GlyphSortType::TEXTURE:
			std::stable_sort(m_glyphsPointers.begin(), m_glyphsPointers.end(), compareTexture);
			break;
		default:
			break;
		}


	}



	bool SpriteBatch::compareFrontToBack(Glyph *a, Glyph *b)
	{
		return (a->m_depth < b->m_depth);
	}
	bool SpriteBatch::compareBackToFront(Glyph *a, Glyph *b)
	{
		return (a->m_depth > b->m_depth);
	}
	bool SpriteBatch::compareTexture(Glyph *a, Glyph *b)
	{
		return (a->m_texture < b->m_texture); //texture returns int so it will compare ints of textures or ids 
	}

	//GLYPH METHODS
	Glyph::Glyph(const glm::vec4 &DestRect, const glm::vec4 &UVRect,
		GLuint Texture, float Depth, const ColorRGBA8 &Color)
		:
		m_texture(Texture),
		m_depth(Depth)
	{
		//sets up new glyph NOTE REMEBER TO DELETE THIS FOR MEMORY LEAKS

		m_topLeft.color = Color;
		m_topLeft.setPosition(DestRect.x, DestRect.y + DestRect.w);
		m_topLeft.setUV(UVRect.x, UVRect.y + UVRect.w);

		m_bottomLeft.color = Color;
		m_bottomLeft.setPosition(DestRect.x, DestRect.y);
		m_bottomLeft.setUV(UVRect.x, UVRect.y);

		m_bottomRight.color = Color;
		m_bottomRight.setPosition(DestRect.x + DestRect.z, DestRect.y);
		m_bottomRight.setUV(UVRect.x + UVRect.z, UVRect.y);

		m_topRight.color = Color;
		m_topRight.setPosition(DestRect.x + DestRect.z, DestRect.y + DestRect.w);
		m_topRight.setUV(UVRect.x + UVRect.z, UVRect.y + UVRect.w);
	}

	Glyph::Glyph(const glm::vec4 &DestRect, const glm::vec4 &UVRect,
		GLuint Texture, float Depth, const ColorRGBA8 &Color, float angle) :
		m_texture(Texture),
		m_depth(Depth)
	{
		glm::vec2 halfDimensions(DestRect.z / 2.0f, DestRect.w / 2.0f);//z width, w height

		//this ii center of sprite
		glm::vec2 topLeft(-halfDimensions.x, halfDimensions.y);
		glm::vec2 bottomLeft(-halfDimensions.x, -halfDimensions.y);
		glm::vec2 bottomRight(halfDimensions.x, -halfDimensions.y);
		glm::vec2 topRight(halfDimensions.x, halfDimensions.y);

		//rotate points
		topLeft = rotatePoint(topLeft, angle) + halfDimensions;
		bottomLeft = rotatePoint(bottomLeft, angle) + halfDimensions;
		bottomRight = rotatePoint(bottomRight, angle) + halfDimensions;
		topRight = rotatePoint(topRight, angle) + halfDimensions;



		//sets up new glyph NOTE REMEBER TO DELETE THIS FOR MEMORY LEAKS

		m_topLeft.color = Color;
		m_topLeft.setPosition(DestRect.x + topLeft.x, DestRect.y + topLeft.y);
		m_topLeft.setUV(UVRect.x, UVRect.y + UVRect.w);

		m_bottomLeft.color = Color;
		m_bottomLeft.setPosition(DestRect.x + bottomLeft.x, DestRect.y + bottomLeft.y);
		m_bottomLeft.setUV(UVRect.x, UVRect.y);

		m_bottomRight.color = Color;
		m_bottomRight.setPosition(DestRect.x + bottomRight.x, DestRect.y + bottomRight.y);
		m_bottomRight.setUV(UVRect.x + UVRect.z, UVRect.y);

		m_topRight.color = Color;
		m_topRight.setPosition(DestRect.x +topRight.x, DestRect.y + topRight.y);
		m_topRight.setUV(UVRect.x + UVRect.z, UVRect.y + UVRect.w);
	}

	glm::vec2 Glyph::rotatePoint(glm::vec2 position, float angle)
	{
		glm::vec2 newVector;
		newVector.x = position.x * std::cos(angle) - position.y *std::sin(angle);
		newVector.y = position.x * std::sin(angle) + position.y *std::cos(angle);
		return newVector;
	}

}