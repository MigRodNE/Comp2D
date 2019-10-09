/* TransformComponent.h -- 'Comp2D' Game Engine 'TransformComponent' class header file
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

#ifndef Comp2D_HEADERS_COMPONENTS_TRANSFORMCOMPONENT_H_
#define Comp2D_HEADERS_COMPONENTS_TRANSFORMCOMPONENT_H_

#include "Box2D/Common/b2Math.h"
#include "Box2D/Common/b2Settings.h"

#include "Comp2D/Headers/Components/Component.h"
#include "Comp2D/Headers/Components/GameObjectBehaviors/ObjectPool.h"
#include "Comp2D/Headers/Objects/GameObject.h"
#include "Comp2D/Headers/States/GameState.h"
#include "Comp2D/Headers/States/PhysicsGameState.h"
#include "Comp2D/Headers/Utilities/Vector2D.h"

namespace Comp2D
{
	namespace Components
	{
		class TransformComponent : public Component
		{
		protected:
			float32 m_localRotation;
			float32 m_worldRotation;

			b2Vec2 m_localPosition;
			b2Vec2 m_localScale;
			b2Vec2 m_worldPosition;
			b2Vec2 m_worldScale;

			virtual void updateTransform() = 0;

		public:
			TransformComponent
			(
				unsigned int id,
				Comp2D::Objects::GameObject* gameObject,
				b2Vec2 localPosition = { 0.0f, 0.0f },
				float32 localRotation = 0.0f,
				b2Vec2 localScale = { 1.0f, 1.0f }
			);

			virtual ~TransformComponent();

			static b2Vec2 getPhysicsWorldPosition( const b2Vec2& screenPosition );

			static Comp2D::Utilities::Vector2D<int> getScreenPosition( const b2Vec2& physicsWorldPosition );

			virtual b2Vec2 getPhysicsWorldPosition() const = 0;

			virtual Comp2D::Utilities::Vector2D<int> getScreenPosition() const = 0;

			virtual void setLocalPosition( b2Vec2 position );
			virtual void setLocalRotation( float32 rotation );
			virtual void setLocalScale( b2Vec2 scale );
			virtual void setWorldPosition( b2Vec2 position );
			virtual void setWorldRotation( float32 rotation );
			virtual void setWorldScale( b2Vec2 scale );

			void rotate( float32 rotation );
			void setLocalPosition( float32 x, float32 y );
			void setLocalScale( float32 x, float32 y );
			void setWorldPosition( float32 x, float32 y );
			void setWorldScale( float32 x, float32 y );
			void translate( b2Vec2 translation );
			void translate( float32 x, float32 y );

			float32 getLocalRotation() const;
			float32 getLocalRotationInRadians() const;
			//float32 getLocalRotationUpTo360() const;
			float32 getWorldRotation() const;
			float32 getWorldRotationInRadians() const;
			//float32 getWorldRotationUpTo360() const;

			b2Vec2 getLocalPosition() const;
			b2Vec2 getLocalScale() const;
			b2Vec2 getWorldPosition() const;
			b2Vec2 getWorldScale() const;

			friend class Comp2D::States::GameState;
			friend class Comp2D::States::PhysicsGameState;
			friend class Comp2D::Components::GameObjectBehaviors::ObjectPool;
		};
	}
}

#endif /* Comp2D_HEADERS_COMPONENTS_TRANSFORMCOMPONENT_H_ */
