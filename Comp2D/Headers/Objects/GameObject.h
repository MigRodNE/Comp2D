/* GameObject.h -- 'Comp2D' Game Engine 'GameObject' class header file
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

#ifndef Comp2D_HEADERS_OBJECTS_GAMEOBJECT_H_
#define Comp2D_HEADERS_OBJECTS_GAMEOBJECT_H_

#include <list>
#include <string>
#include <typeinfo>
#include <vector>

#include <SDL.h>

#include "Box2D/Collision/b2Collision.h"
#include "Box2D/Dynamics/b2WorldCallbacks.h"
#include "Box2D/Dynamics/Contacts/b2Contact.h"

#include "Comp2D/Headers/Objects/Dependency.h"
#include "Comp2D/Headers/States/GameState.h"

// TODO: Utilizar Binary Search nos métodos de get por ID ou por Name
// TODO: BUG: objetoNãoActiveInHierarchy.setChildGameObjectActiveInHierarchy e
//		 	  setChildGameObjectActive
// TODO: (OPCIONAL) removeChildGameObject

namespace Comp2D
{
	namespace Components
	{
		class Component;
		class TransformComponent;
	}

	namespace Objects
	{
		// Add Tags Here
		enum class EGameObjectTag
		{
			Default,
			Player,
			ScenarioObject,
			Ground,
			PassthroughGround,
			Wall,
			PassthroughWall,
			GameObjectTagsCount
		};

		class GameObject
		{
		protected:
			bool m_active;
			bool m_activeInHierarchy;

			unsigned int m_id;

			std::string m_name;

			EGameObjectTag m_tag;

			virtual void setComponentActiveInHierarchy( Comp2D::Components::Component* component, bool activeInHierarchy );
			virtual void setSelfActiveInHierarchy( bool activeInHierarchy );

		public:
			GameObject* parentGameObject = nullptr;

			Comp2D::Components::TransformComponent* transform = nullptr;

			Comp2D::States::GameState* gameState = nullptr;

			std::vector<GameObject*> childGameObjects;

			std::vector<Comp2D::Components::Component*> components;

			std::list<GameObject*> activeChildGameObjects;
			//std::list<GameObject*> activeInHierarchyChildGameObjects;

			//std::list<Comp2D::Components::Component*> activeInHierarchyComponents;
			std::list<Comp2D::Components::Component*> enabledComponents;

			std::list<Dependency*> componentDependencies;

			GameObject
			(
				bool active,
				bool activeInHierarchy,
				unsigned int id,
				const std::string& name,
				Comp2D::States::GameState* gameState,
				EGameObjectTag tag = EGameObjectTag::Default
			);

			virtual ~GameObject();

			bool operator==( const GameObject& rhs ) const;

			bool operator!=( const GameObject& rhs ) const;

			virtual void setActive( bool active );
			virtual void setActiveInHierarchy( bool activeInHierarchy );
			virtual void setChildGameObjectActive( unsigned int id, bool active );
			virtual void setChildGameObjectActive( const std::string& name, bool active );
			virtual void setChildGameObjectActive( GameObject* childGameObject, bool active );
			virtual void setChildGameObjectActiveInHierarchy( unsigned int id, bool activeInHierarchy );
			virtual void setChildGameObjectActiveInHierarchy( const std::string& name, bool activeInHierarchy );
			virtual void setChildGameObjectActiveInHierarchy( GameObject* childGameObject, bool activeInHierarchy );
			virtual void setComponentEnabled( Comp2D::Components::Component* component, bool enabled );

			virtual void onRotated( float32 rotation );
			virtual void onTranslated( b2Vec2 translation );

			virtual void beginContact( b2Contact* contact, GameObject* otherGameObject );
			virtual void endContact( b2Contact* contact, GameObject* otherGameObject );
			virtual void postSolve( b2Contact* contact, const b2ContactImpulse* impulse, GameObject* otherGameObject );
			virtual void preSolve( b2Contact* contact, const b2Manifold* oldManifold, GameObject* otherGameObject );

			virtual bool isActive() const;
			virtual bool isActiveInHierarchy() const;

			unsigned int getID() const;

			const std::string& getName() const;

			EGameObjectTag getTag() const;

			virtual Comp2D::Components::Component* addComponent( Comp2D::Components::Component* component, bool enabled = true );
			virtual Comp2D::Components::Component* getComponent( unsigned int id ) const;
			virtual Comp2D::Components::Component* removeComponent( unsigned int id );
			virtual Comp2D::Components::Component* removeComponent( Comp2D::Components::Component* component );

			template <typename T>
			T* getComponent() const
			{
				#ifdef DEBUG
					/*
					SDL_LogDebug
					(
						SDL_LOG_CATEGORY_TEST,
						"GameObject with ID %u named %s getComponent: typeid(T).name = %s\n",
						m_id,
						m_name.c_str(),
						typeid(T).name()
					);
					*/
				#endif

				T* currentComponent = nullptr;

				for( unsigned int i = 0; i < components.size(); ++i )
				{
					currentComponent = dynamic_cast<T*>( components[i] );

					if( currentComponent )
					{
						return currentComponent;
					}
				}

				return nullptr;
			}

			virtual GameObject* addChildGameObject( GameObject* childGameObject, bool active = true, bool activeInHierarchy = true );
			virtual GameObject* getChildGameObject( unsigned int id ) const;
			virtual GameObject* getChildGameObject( const std::string& name ) const;
			virtual GameObject* removeChildGameObject( unsigned int id, bool deleteChildGameObject );
			virtual GameObject* removeChildGameObject( const std::string& name, bool deleteChildGameObject );
			virtual GameObject* removeChildGameObject( GameObject* childGameObject, bool deleteChildGameObject );

			template <typename T>
			std::list<T*> getComponents() const
			{
				#ifdef DEBUG
					/*
					SDL_LogDebug
					(
						SDL_LOG_CATEGORY_TEST,
						"GameObject with ID %u named %s getComponents: typeid(T).name = %s\n",
						m_id,
						m_name.c_str(),
						typeid(T).name()
					);
					*/
				#endif

				std::list<T*> searchedComponents;

				T* currentComponent = nullptr;

				for( unsigned int i = 0; i < components.size(); ++i )
				{
					currentComponent = dynamic_cast<T*>( components[i] );

					if( currentComponent )
					{
						searchedComponents.push_back( currentComponent );
					}
				}

				return searchedComponents;
			}
		};
	}
}

#endif /* Comp2D_HEADERS_OBJECTS_GAMEOBJECT_H_ */
