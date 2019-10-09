/* PhysicsTransformComponentFixturesShapesRenderer.cpp -- 'Comp2D' Game Engine 'PhysicsTransformComponentFixturesShapesRenderer' class source file
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

#include "Comp2D/Headers/Components/PhysicsTransformComponentFixturesShapesRenderer.h"

#include <cmath>
#include <vector>

#include <SDL.h>

//#include "Box2D/Collision/Shapes/b2ChainShape.h"
#include "Box2D/Collision/Shapes/b2CircleShape.h"
#include "Box2D/Collision/Shapes/b2EdgeShape.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Collision/Shapes/b2Shape.h"
#include "Box2D/Common/b2Math.h"
#include "Box2D/Common/b2Settings.h"
#include "Box2D/Dynamics/b2Fixture.h"

#include "Comp2D/Headers/Game.h"
#include "Comp2D/Headers/Components/Component.h"
#include "Comp2D/Headers/Components/PhysicsTransformComponent.h"
#include "Comp2D/Headers/Components/Renderable.h"
#include "Comp2D/Headers/Components/TransformComponent.h"
#include "Comp2D/Headers/Objects/GameObject.h"
#include "Comp2D/Headers/States/PhysicsGameState.h"
#include "Comp2D/Headers/Utilities/Vector2D.h"

Comp2D::Components::PhysicsTransformComponentFixturesShapesRenderer::PhysicsTransformComponentFixturesShapesRenderer
(
	unsigned int id,
	Comp2D::Objects::GameObject* gameObject
)
	:
	Component( id, gameObject ),
	Renderable()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponentFixturesShapesRenderer with ID %u (From GameObject with ID %u named %s) Constructor body Start\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponentFixturesShapesRenderer with ID %u (From GameObject with ID %u named %s) Constructor body End\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

Comp2D::Components::PhysicsTransformComponentFixturesShapesRenderer::~PhysicsTransformComponentFixturesShapesRenderer()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponentFixturesShapesRenderer with ID %u (From GameObject with ID %u named %s) Destroying\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponentFixturesShapesRenderer with ID %u (From GameObject with ID %u named %s) Destroyed\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::PhysicsTransformComponentFixturesShapesRenderer::drawChainShape( b2Shape* shape )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponentFixturesShapesRenderer with ID %u (From GameObject with ID %u named %s) drawChainShape\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponentFixturesShapesRenderer with ID %u (From GameObject with ID %u named %s) Not Implemented\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::PhysicsTransformComponentFixturesShapesRenderer::drawCircleShape( b2Shape* shape )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponentFixturesShapesRenderer with ID %u (From GameObject with ID %u named %s) drawCircleShape\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	b2CircleShape* circleShape = dynamic_cast<b2CircleShape*>( shape );

	std::vector<SDL_Point> pointsVector;

	Comp2D::Utilities::Vector2D<int> circleScreenPosition = physicsTransformComponent->getScreenPosition();

	int x0 = circleScreenPosition.x;
	int y0 = circleScreenPosition.y;
	int radius = static_cast<int>( round( circleShape->m_radius / Comp2D::States::PhysicsGameState::scaleFactor ) );
	int x = radius - 1;
	int y = 0;
	int dx = 1;
	int dy = 1;
	int err = dx - ( radius << 1 );

	while( x >= y )
	{
		pointsVector.push_back( SDL_Point{ x0 + x, y0 + y } );
		pointsVector.push_back( SDL_Point{ x0 + y, y0 + x } );
		pointsVector.push_back( SDL_Point{ x0 - y, y0 + x } );
		pointsVector.push_back( SDL_Point{ x0 - x, y0 + y } );
		pointsVector.push_back( SDL_Point{ x0 - x, y0 - y } );
		pointsVector.push_back( SDL_Point{ x0 - y, y0 - x } );
		pointsVector.push_back( SDL_Point{ x0 + y, y0 - x } );
		pointsVector.push_back( SDL_Point{ x0 + x, y0 - y } );

		if( err <= 0 )
		{
			y++;
			err += dy;
			dy += 2;
		}

		if( err > 0 )
		{
			x--;
			dx += 2;
			err += dx - ( radius << 1 );
		}
	}

	SDL_RenderDrawPoints( Comp2D::Game::renderer, &pointsVector[0], static_cast<int>( pointsVector.size() ) );
}

void Comp2D::Components::PhysicsTransformComponentFixturesShapesRenderer::drawEdgeShape( b2Shape* shape )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponentFixturesShapesRenderer with ID %u (From GameObject with ID %u named %s) drawEdgeShape\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	b2EdgeShape* edgeShape = dynamic_cast<b2EdgeShape*>( shape );

	Comp2D::Utilities::Vector2D<int> edgeVertex1ScreenPosition = TransformComponent::getScreenPosition
	(
		physicsTransformComponent->getWorldPoint( edgeShape->m_vertex1 )
	);

	Comp2D::Utilities::Vector2D<int> edgeVertex2ScreenPosition = TransformComponent::getScreenPosition
	(
		physicsTransformComponent->getWorldPoint( edgeShape->m_vertex2 )
	);

	SDL_RenderDrawLine
	(
		Comp2D::Game::renderer,
		edgeVertex1ScreenPosition.x,
		edgeVertex1ScreenPosition.y,
		edgeVertex2ScreenPosition.x,
		edgeVertex2ScreenPosition.y
	);
}

void Comp2D::Components::PhysicsTransformComponentFixturesShapesRenderer::drawFixtureShape( b2Fixture* fixture )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponentFixturesShapesRenderer with ID %u (From GameObject with ID %u named %s) drawFixtureShape\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	b2Shape* shape = fixture->GetShape();

	b2Shape::Type shapeType = shape->GetType();

	switch( shapeType )
	{
	case b2Shape::Type::e_chain:
		drawChainShape( shape );
		break;
	case b2Shape::Type::e_circle:
		drawCircleShape( shape );
		break;
	case b2Shape::Type::e_edge:
		drawEdgeShape( shape );
		break;
	case b2Shape::Type::e_polygon:
		drawPolygonShape( shape );
		break;
	default:
		break;
	}
}

void Comp2D::Components::PhysicsTransformComponentFixturesShapesRenderer::drawPolygonShape( b2Shape* shape )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponentFixturesShapesRenderer with ID %u (From GameObject with ID %u named %s) drawPolygonShape\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	b2PolygonShape* polygonShape = dynamic_cast<b2PolygonShape*>( shape );

	int32 vertexCount = sizeof( polygonShape->m_vertices ) / sizeof( *polygonShape->m_vertices );

	int32 vertexPointsTotalCount = vertexCount + 1;

	SDL_Point* vertexPoints = new SDL_Point[vertexPointsTotalCount];

	Comp2D::Utilities::Vector2D<int> currentPointScreenPosition;
	for( int32 i = 0; i < vertexCount; ++i )
	{
		currentPointScreenPosition = TransformComponent::getScreenPosition
		(
			physicsTransformComponent->getWorldPoint( polygonShape->m_vertices[i] )
		);
		vertexPoints[i] = SDL_Point{ currentPointScreenPosition.x, currentPointScreenPosition.y };
	}
	currentPointScreenPosition = TransformComponent::getScreenPosition
	(
		physicsTransformComponent->getWorldPoint( polygonShape->m_vertices[0] )
	);
	vertexPoints[vertexCount] = SDL_Point{ currentPointScreenPosition.x, currentPointScreenPosition.y };

	SDL_RenderDrawLines( Comp2D::Game::renderer, vertexPoints, vertexCount + 1 );

	delete[] vertexPoints;
}

void Comp2D::Components::PhysicsTransformComponentFixturesShapesRenderer::debugLogComponentData() const
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponentFixturesShapesRenderer with ID %u (From GameObject with ID %u named %s) debugLogComponentData\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::PhysicsTransformComponentFixturesShapesRenderer::onActivateInHierarchy()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponentFixturesShapesRenderer with ID %u (From GameObject with ID %u named %s) onActivateInHierarchy\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::PhysicsTransformComponentFixturesShapesRenderer::onDeactivateInHierarchy()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponentFixturesShapesRenderer with ID %u (From GameObject with ID %u named %s) onDeactivateInHierarchy\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::PhysicsTransformComponentFixturesShapesRenderer::onDelete()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponentFixturesShapesRenderer with ID %u (From GameObject with ID %u named %s) onDelete\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::PhysicsTransformComponentFixturesShapesRenderer::onDisable()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponentFixturesShapesRenderer with ID %u (From GameObject with ID %u named %s) onDisable\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::PhysicsTransformComponentFixturesShapesRenderer::onEnable()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponentFixturesShapesRenderer with ID %u (From GameObject with ID %u named %s) onEnable\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::PhysicsTransformComponentFixturesShapesRenderer::onFinalizeState()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponentFixturesShapesRenderer with ID %u (From GameObject with ID %u named %s) onFinalizeState\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::PhysicsTransformComponentFixturesShapesRenderer::onInitializeState()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponentFixturesShapesRenderer with ID %u (From GameObject with ID %u named %s) onInitializeState\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::PhysicsTransformComponentFixturesShapesRenderer::onInstantiated()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponentFixturesShapesRenderer with ID %u (From GameObject with ID %u named %s) onInstantiated\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	physicsTransformComponent = dynamic_cast<Comp2D::Components::PhysicsTransformComponent*>( gameObject->transform );

	m_executedOnInstantiated = true;
}

void Comp2D::Components::PhysicsTransformComponentFixturesShapesRenderer::onPaused()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponentFixturesShapesRenderer with ID %u (From GameObject with ID %u named %s) onPaused\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif
}

void Comp2D::Components::PhysicsTransformComponentFixturesShapesRenderer::onUnpaused()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponentFixturesShapesRenderer with ID %u (From GameObject with ID %u named %s) onUnpaused\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif
}

void Comp2D::Components::PhysicsTransformComponentFixturesShapesRenderer::render()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponentFixturesShapesRenderer with ID %u (From GameObject with ID %u named %s) render\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

    SDL_SetRenderDrawColor( Comp2D::Game::renderer, 255, 255, 0, SDL_ALPHA_OPAQUE );

    if( physicsTransformComponent )
    {
    	for
		(
			b2Fixture* fixture = physicsTransformComponent->getFixtureList();
			fixture;
			fixture = fixture->GetNext()
    	)
    	{
    		drawFixtureShape( fixture );
    	}
    }
}
