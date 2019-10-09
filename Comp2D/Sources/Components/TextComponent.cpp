/* TextComponent.cpp -- 'Comp2D' Game Engine 'TextComponent' class source file
  version 1.0.0, October 9th, 2019

  Copyright (C) 2018-2019 Miguel Rodrigo Auto Gomes

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
	 claim that you wrote the original software. If you use this software
	 in a product, an acknowledgment in the product documentation would be
	 appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
	 misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

  Miguel Rodrigo Auto Gomes
  migrodne@gmail.com

*/

#include "Comp2D/Headers/Components/TextComponent.h"

#include <cmath>
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "Comp2D/Headers/Game.h"
#include "Comp2D/Headers/Components/GraphicsComponent.h"
#include "Comp2D/Headers/Components/TransformComponent.h"
#include "Comp2D/Headers/Objects/GameObject.h"
#include "Comp2D/Headers/Resources/FontResource.h"
#include "Comp2D/Headers/Resources/Resource.h"
#include "Comp2D/Headers/Utilities/Vector2D.h"

Comp2D::Components::TextComponent::TextComponent
(
	unsigned int id,
	Comp2D::Objects::GameObject* gameObject,
	const std::string& text,
	SDL_Color color,
	Comp2D::Resources::FontResource* resource
)
	:
	GraphicsComponent( id, gameObject ),
	m_text( text ),
	m_screenPositionOffset( 0, 0 ),
	m_color( color )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TextComponent with ID %u (From GameObject with ID %u named %s) Constructor body Start\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	setResource( resource );

	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TextComponent with ID %u (From GameObject with ID %u named %s) Constructor body End\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

Comp2D::Components::TextComponent::~TextComponent()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TextComponent with ID %u (From GameObject with ID %u named %s) Destroying\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	SDL_DestroyTexture( m_renderedTextTexture );
	m_renderedTextTexture = nullptr;

	SDL_FreeSurface( m_renderedTextSurface );
	m_renderedTextSurface = nullptr;

	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TextComponent with ID %u (From GameObject with ID %u named %s) Destroyed\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::TextComponent::renderTextTexture()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TextComponent with ID %u (From GameObject with ID %u named %s) renderTextTexture\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	if( m_renderedTextTexture )
	{
		SDL_DestroyTexture( m_renderedTextTexture );
		m_renderedTextTexture = nullptr;

		SDL_FreeSurface( m_renderedTextSurface );
		m_renderedTextSurface = nullptr;
	}

	if( !m_text.empty() )
	{
		m_renderedTextSurface = TTF_RenderText_Solid
		(
			getResource()->getFont(),
			m_text.c_str(),
			m_color
		);

		if( m_renderedTextSurface )
		{
			m_renderedTextRect.x = 0;
			m_renderedTextRect.y = 0;
			m_renderedTextRect.w = m_renderedTextSurface->w;
			m_renderedTextRect.h = m_renderedTextSurface->h;

			m_renderedTextTexture = SDL_CreateTextureFromSurface( Comp2D::Game::renderer, m_renderedTextSurface );
		}
	}
}

void Comp2D::Components::TextComponent::debugLogComponentData() const
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TextComponent with ID %u (From GameObject with ID %u named %s) debugLogComponentData\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::TextComponent::onActivateInHierarchy()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TextComponent with ID %u (From GameObject with ID %u named %s) onActivateInHierarchy\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::TextComponent::onDeactivateInHierarchy()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TextComponent with ID %u (From GameObject with ID %u named %s) onDeactivateInHierarchy\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::TextComponent::onDelete()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TextComponent with ID %u (From GameObject with ID %u named %s) onDelete\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::TextComponent::onDisable()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TextComponent with ID %u (From GameObject with ID %u named %s) onDisable\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::TextComponent::onEnable()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TextComponent with ID %u (From GameObject with ID %u named %s) onEnable\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::TextComponent::onFinalizeState()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TextComponent with ID %u (From GameObject with ID %u named %s) onFinalizeState\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::TextComponent::onInitializeState()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TextComponent with ID %u (From GameObject with ID %u named %s) onInitializeState\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	renderTextTexture();
}

void Comp2D::Components::TextComponent::onInstantiated()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TextComponent with ID %u (From GameObject with ID %u named %s) onInstantiated\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	m_executedOnInstantiated = true;
}

void Comp2D::Components::TextComponent::onPaused()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TextComponent with ID %u (From GameObject with ID %u named %s) onPaused\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif
}

void Comp2D::Components::TextComponent::onUnpaused()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TextComponent with ID %u (From GameObject with ID %u named %s) onUnpaused\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif
}

void Comp2D::Components::TextComponent::setResource( Comp2D::Resources::Resource* resource )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TextComponent with ID %u (From GameObject with ID %u named %s) setResource named %s\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			resource->getName().c_str()
		);
		*/
	#endif

	Comp2D::Resources::FontResource* fontResource = dynamic_cast<Comp2D::Resources::FontResource*>( resource );

	if( fontResource )
	{
		m_resource = fontResource;
	}
	else
	{
		// TODO: Lançar exceção
	}
}

void Comp2D::Components::TextComponent::render()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TextComponent with ID %u (From GameObject with ID %u named %s) render\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	if( m_renderedTextTexture )
	{
		float64 textAngle;

		SDL_Rect textScreenRect;

		Comp2D::Utilities::Vector2D<int> textScreenPosition;

		if( gameObject->transform )
		{
			textScreenPosition = gameObject->transform->getScreenPosition() + m_screenPositionOffset;

			b2Vec2 gameObjectWorldScale = gameObject->transform->getWorldScale();
			textScreenRect.w = static_cast<int>( round( m_renderedTextSurface->w * gameObjectWorldScale.x ) );
			textScreenRect.h = static_cast<int>( round( m_renderedTextSurface->h * gameObjectWorldScale.y ) );

			textAngle = -static_cast<float64>( gameObject->transform->getWorldRotation() );
		}

		textScreenRect.x = textScreenPosition.x;
		textScreenRect.y = textScreenPosition.y;

		SDL_RenderCopyEx
		(
			Comp2D::Game::renderer,
			m_renderedTextTexture,
			&m_renderedTextRect,
			&textScreenRect,
			textAngle,
			nullptr,
			SDL_FLIP_NONE
		);
	}
}

Comp2D::Resources::FontResource* Comp2D::Components::TextComponent::getResource() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TextComponent with ID %u (From GameObject with ID %u named %s) getResource\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return static_cast<Comp2D::Resources::FontResource*>( m_resource );
}

void Comp2D::Components::TextComponent::setColor( SDL_Color color )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TextComponent with ID %u (From GameObject with ID %u named %s) setColor: color = ( %i, %i, %i )\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			color.r,
			color.g,
			color.b
		);
	#endif

	m_color = color;

	renderTextTexture();
}

void Comp2D::Components::TextComponent::setFontPointSize( int pointSize )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TextComponent with ID %u (From GameObject with ID %u named %s) setFontPointSize: pointSize = %i\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			pointSize
		);
	#endif

	getResource()->setPointSize( pointSize );

	if( getResource()->isLoaded() )
	{
		renderTextTexture();
	}
}

void Comp2D::Components::TextComponent::setScreenPositionOffset( Comp2D::Utilities::Vector2D<int> screenPositionOffset )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TextComponent with ID %u (From GameObject with ID %u named %s) setScreenPositionOffset: screenPositionOffset = ( %i, %i )\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			screenPositionOffset.x,
			screenPositionOffset.y
		);
		*/
	#endif

	m_screenPositionOffset = screenPositionOffset;
}

void Comp2D::Components::TextComponent::setText( const std::string& text )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TextComponent with ID %u (From GameObject with ID %u named %s) setText: text = %s\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			text.c_str()
		);
		*/
	#endif

	m_text = text;

	renderTextTexture();
}

std::string Comp2D::Components::TextComponent::getText() const
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TextComponent with ID %u (From GameObject with ID %u named %s) getText\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	return m_text;
}

Comp2D::Utilities::Vector2D<int> Comp2D::Components::TextComponent::getScreenPositionOffset() const
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TextComponent with ID %u (From GameObject with ID %u named %s) getScreenPositionOffset\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	return m_screenPositionOffset;
}

SDL_Rect Comp2D::Components::TextComponent::getRenderedTextRect() const
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TextComponent with ID %u (From GameObject with ID %u named %s) getRenderedTextRect\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	return m_renderedTextRect;
}

SDL_Color Comp2D::Components::TextComponent::getColor() const
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TextComponent with ID %u (From GameObject with ID %u named %s) getColor\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	return m_color;
}
