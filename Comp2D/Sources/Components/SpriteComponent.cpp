/* SpriteComponent.cpp -- 'Comp2D' Game Engine 'SpriteComponent' class source file
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

#include "Comp2D/Headers/Components/SpriteComponent.h"

#include <cmath>

#include <SDL.h>

#include "Comp2D/Headers/Game.h"
#include "Comp2D/Headers/Components/GraphicsComponent.h"
#include "Comp2D/Headers/Components/TransformComponent.h"
#include "Comp2D/Headers/Objects/GameObject.h"
#include "Comp2D/Headers/Resources/Resource.h"
#include "Comp2D/Headers/Resources/TextureResource.h"
#include "Comp2D/Headers/Utilities/Vector2D.h"

Comp2D::Components::SpriteComponent::SpriteComponent
(
	unsigned int id,
	Comp2D::Objects::GameObject* gameObject,
	SDL_RendererFlip flipState,
	SDL_Point pivot,
	SDL_Rect spriteRect,
	Comp2D::Resources::TextureResource* resource
)
	:
	GraphicsComponent( id, gameObject ),
	m_flipState( flipState ),
	m_pivot( pivot ),
	m_spriteRect( spriteRect )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SpriteComponent with ID %u (From GameObject with ID %u named %s) Constructor body Start\n",
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
			"SpriteComponent with ID %u (From GameObject with ID %u named %s) Constructor body End\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

Comp2D::Components::SpriteComponent::~SpriteComponent()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SpriteComponent with ID %u (From GameObject with ID %u named %s) Destroying\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SpriteComponent with ID %u (From GameObject with ID %u named %s) Destroyed\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::SpriteComponent::debugLogComponentData() const
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SpriteComponent with ID %u (From GameObject with ID %u named %s) debugLogComponentData\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::SpriteComponent::onActivateInHierarchy()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SpriteComponent with ID %u (From GameObject with ID %u named %s) onActivateInHierarchy\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::SpriteComponent::onDeactivateInHierarchy()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SpriteComponent with ID %u (From GameObject with ID %u named %s) onDeactivateInHierarchy\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::SpriteComponent::onDelete()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SpriteComponent with ID %u (From GameObject with ID %u named %s) onDelete\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::SpriteComponent::onDisable()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SpriteComponent with ID %u (From GameObject with ID %u named %s) onDisable\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::SpriteComponent::onEnable()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SpriteComponent with ID %u (From GameObject with ID %u named %s) onEnable\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::SpriteComponent::onFinalizeState()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SpriteComponent with ID %u (From GameObject with ID %u named %s) onFinalizeState\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::SpriteComponent::onInitializeState()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SpriteComponent with ID %u (From GameObject with ID %u named %s) onInitializeState\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	m_texture = getResource()->getTexture();
}

void Comp2D::Components::SpriteComponent::onInstantiated()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SpriteComponent with ID %u (From GameObject with ID %u named %s) onInstantiated\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	m_executedOnInstantiated = true;
}

void Comp2D::Components::SpriteComponent::onPaused()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SpriteComponent with ID %u (From GameObject with ID %u named %s) onPaused\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif
}

void Comp2D::Components::SpriteComponent::onUnpaused()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SpriteComponent with ID %u (From GameObject with ID %u named %s) onUnpaused\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif
}

void Comp2D::Components::SpriteComponent::setResource( Comp2D::Resources::Resource* resource )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SpriteComponent with ID %u (From GameObject with ID %u named %s) setResource named %s\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			resource->getName().c_str()
		);
		*/
	#endif

	Comp2D::Resources::TextureResource* textureResource = dynamic_cast<Comp2D::Resources::TextureResource*>( resource );

	if( textureResource )
	{
		m_resource = textureResource;

		if( m_texture )
		{
			m_texture = getResource()->getTexture();
		}
	}
	else
	{
		// TODO: Lançar exceção
	}
}

void Comp2D::Components::SpriteComponent::render()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SpriteComponent with ID %u (From GameObject with ID %u named %s) render\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	float64 spriteAngle;

	SDL_Point pivot;

	SDL_Rect spriteScreenRect;

	Comp2D::Utilities::Vector2D<int> spriteScreenPosition;

	if( gameObject->transform )
	{
		spriteScreenPosition = gameObject->transform->getScreenPosition();

		spriteAngle = -static_cast<float64>( gameObject->transform->getWorldRotation() );

		b2Vec2 gameObjectWorldScale = gameObject->transform->getWorldScale();

		pivot.x = static_cast<int>( round( m_pivot.x * gameObjectWorldScale.x ) );
		pivot.y = static_cast<int>( round( m_pivot.y * gameObjectWorldScale.y ) );

		spriteScreenRect.w = static_cast<int>( round( m_spriteRect.w * gameObjectWorldScale.x ) );
		spriteScreenRect.h = static_cast<int>( round( m_spriteRect.h * gameObjectWorldScale.y ) );
	}

	spriteScreenRect.x = spriteScreenPosition.x - pivot.x;
	spriteScreenRect.y = spriteScreenPosition.y - pivot.y;

	SDL_RenderCopyEx
	(
		Comp2D::Game::renderer,
		m_texture,
		&m_spriteRect,
		&spriteScreenRect,
		spriteAngle,
		&pivot,
		m_flipState
	);
}

Comp2D::Resources::TextureResource* Comp2D::Components::SpriteComponent::getResource() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SpriteComponent with ID %u (From GameObject with ID %u named %s) getResource\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return static_cast<Comp2D::Resources::TextureResource*>( m_resource );
}

void Comp2D::Components::SpriteComponent::setFlipState( SDL_RendererFlip flipState )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SpriteComponent with ID %u (From GameObject with ID %u named %s) setFlipState: flipState = %i\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			static_cast<int>( flipState )
		);
		*/
	#endif

	m_flipState = flipState;
}

void Comp2D::Components::SpriteComponent::setModColor( Uint8 r, Uint8 g, Uint8 b )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SpriteComponent with ID %u (From GameObject with ID %u named %s) setModColor: r = %u; g = %u; b = %u\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			r,
			g,
			b
		);
		*/
	#endif

	getResource()->setModColor( r, g, b );

	m_texture = getResource()->getTexture();
}

void Comp2D::Components::SpriteComponent::setPivot( SDL_Point pivot )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SpriteComponent with ID %u (From GameObject with ID %u named %s) setPivot: pivot = ( %i, %i )\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			pivot.x,
			pivot.y
		);
		*/
	#endif

	m_pivot = pivot;
}

void Comp2D::Components::SpriteComponent::setPivotToCenter()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SpriteComponent with ID %u (From GameObject with ID %u named %s) setPivotToCenter\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	m_pivot.x = m_spriteRect.w / 2;
	m_pivot.y = m_spriteRect.h / 2;
}

void Comp2D::Components::SpriteComponent::setSpriteRect( SDL_Rect spriteRect )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SpriteComponent with ID %u (From GameObject with ID %u named %s) setSpriteRect: spriteRect = ( %i, %i, %i, %i )\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			spriteRect.x,
			spriteRect.y,
			spriteRect.w,
			spriteRect.h
		);
		*/
	#endif

	m_spriteRect = spriteRect;
}

SDL_RendererFlip Comp2D::Components::SpriteComponent::getFlipState() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SpriteComponent with ID %u (From GameObject with ID %u named %s) getFlipState\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_flipState;
}

SDL_Point Comp2D::Components::SpriteComponent::getPivot() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SpriteComponent with ID %u (From GameObject with ID %u named %s) getPivot\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_pivot;
}

SDL_Rect Comp2D::Components::SpriteComponent::getSpriteRect() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SpriteComponent with ID %u (From GameObject with ID %u named %s) getSpriteRect\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_spriteRect;
}

const SDL_Color& Comp2D::Components::SpriteComponent::getModColor() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SpriteComponent with ID %u (From GameObject with ID %u named %s) getModColor\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return getResource()->getModColor();
}
