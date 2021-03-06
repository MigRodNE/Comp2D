/* GraphicsComponent.cpp -- 'Comp2D' Game Engine 'GraphicsComponent' class source file
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

#include "Comp2D/Headers/Components/GraphicsComponent.h"

#include "Comp2D/Headers/Components/Renderable.h"
#include "Comp2D/Headers/Components/ResourceComponent.h"
#include "Comp2D/Headers/Objects/GameObject.h"

Comp2D::Components::GraphicsComponent::GraphicsComponent
(
	unsigned int id,
	Comp2D::Objects::GameObject* gameObject
)
	:
	ResourceComponent( id, gameObject ),
	Renderable()
{
#ifdef DEBUG
	SDL_LogDebug
	(
		SDL_LOG_CATEGORY_TEST,
		"GraphicsComponent with ID %u (From GameObject with ID %u named %s) Constructor body Start\n",
		m_id,
		gameObject->getID(),
		gameObject->getName().c_str()
	);
#endif

#ifdef DEBUG
	SDL_LogDebug
	(
		SDL_LOG_CATEGORY_TEST,
		"GraphicsComponent with ID %u (From GameObject with ID %u named %s) Constructor body End\n",
		m_id,
		gameObject->getID(),
		gameObject->getName().c_str()
	);
#endif
}

Comp2D::Components::GraphicsComponent::~GraphicsComponent()
{
#ifdef DEBUG
	SDL_LogDebug
	(
		SDL_LOG_CATEGORY_TEST,
		"GraphicsComponent with ID %u (From GameObject with ID %u named %s) Destroying\n",
		m_id,
		gameObject->getID(),
		gameObject->getName().c_str()
	);
#endif

#ifdef DEBUG
	SDL_LogDebug
	(
		SDL_LOG_CATEGORY_TEST,
		"GraphicsComponent with ID %u (From GameObject with ID %u named %s) Destroyed\n",
		m_id,
		gameObject->getID(),
		gameObject->getName().c_str()
	);
#endif
}
