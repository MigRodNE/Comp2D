/* PhysicsTransformComponent.h -- 'Comp2D' Game Engine 'PhysicsTransformComponent' class header file
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

#ifndef Comp2D_HEADERS_COMPONENTS_PHYSICSTRANSFORMCOMPONENT_H_
#define Comp2D_HEADERS_COMPONENTS_PHYSICSTRANSFORMCOMPONENT_H_

#include <list>
#include <vector>

#include "Box2D/Collision/Shapes/b2Shape.h"
#include "Box2D/Common/b2Math.h"
#include "Box2D/Common/b2Settings.h"
#include "Box2D/Dynamics/b2Body.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "Box2D/Dynamics/b2World.h"
#include "Box2D/Dynamics/Contacts/b2Contact.h"
#include "Box2D/Dynamics/Joints/b2Joint.h"

#include "Comp2D/Headers/Components/TransformComponent.h"
#include "Comp2D/Headers/Objects/GameObject.h"
#include "Comp2D/Headers/Utilities/Vector2D.h"

// OBS: LEMBRAR DE ADICIONAR/CONSTRUIR O PHYSICS COMPONENT ANTES DOS FIXTUREDEFCOMPONENTS!!!!

// TODO: updateWorldPosition/Rotation com parentGameObject com TransformComponent
// TODO: updateWorldPosition/Rotation com parentGameObject com PhysicsComponent
// TODO: Lidar com Associação entre Fixtures como Parent/Child Fixtures
//		 (considerar unificar FixtureDefComponent com PhysicsComponent -cada Fixture
//		 teria um body- em uma classe ShapeComponent; criar uma classe "Body Container"
//		 -RigidbodyComponent- que gerenciaria todos os bodys de um objeto e seus
//		 childObjects)
// TODO: Lidar com mudança de Scale do objeto (considerar mudança no scalingFactor)
//		 - setLocalScale
//		 - updateWorldScale()
//		 - updateChildObjectsScale()
//		 - setWorldScale
//		 - updateLocalScale()
// TODO: métodos applyForce/Torque/etc. nos physics dos childGameObjects
// TODO: (OPCIONAL) colocar os seguintes dados para printar no debugLogComponentData:
//		 - IsAwake
//		 - IsBullet
//		 - IsFixedRotation
//		 - IsSleepingAllowed
//		 - GetAngularDamping
//		 - GetAngularVelocity
//		 - GetInertia
//		 - GetLinearDamping
//		 - GetMass
//		 - GetFixtureList
//		 - GetJointList
//		 - GetContactList
//		 - GetNext()

namespace Comp2D
{
	namespace Components
	{
		class FixtureDefComponent;

		class PhysicsTransformComponent : public TransformComponent
		{
		protected:
			b2Body* m_body = nullptr;

			void updateTransform() override;

		public:
			PhysicsTransformComponent
			(
				unsigned int id,
				Comp2D::Objects::GameObject* gameObject,
				b2World* world,
				b2BodyDef def
			);

			PhysicsTransformComponent
			(
				unsigned int id,
				Comp2D::Objects::GameObject* gameObject,
				b2World* world,
				b2BodyType type = b2_staticBody,
				b2Vec2 position = { 0.0f, 0.0f },
				float32 angle = 0.0f,
				b2Vec2 linearVelocity = { 0.0f, 0.0f },
				float32 angularVelocity = 0.0f,
				float32 linearDamping = 0.0f,
				float32 angularDamping = 0.0f,
				bool allowSleep = true,
				bool awake = true,
				bool fixedRotation = false,
				bool bullet = false,
				float32 gravityScale = 1.0f
			);

			~PhysicsTransformComponent();

			void debugLogComponentData() const override;

			void onActivateInHierarchy() override;
			void onDeactivateInHierarchy() override;
			void onDelete() override;
			void onDisable() override;
			void onEnable() override;
			void onFinalizeState() override;
			void onInitializeState() override;
			void onInstantiated() override;
			void onPaused() override;
			void onUnpaused() override;

			b2Vec2 getPhysicsWorldPosition() const override;

			Comp2D::Utilities::Vector2D<int> getScreenPosition() const override;

			void applyAngularImpulse( float32 impulse, bool wake );
			void applyForce( const b2Vec2& force, const b2Vec2& point, bool wake );
			void applyForceToCenter( const b2Vec2& force, bool wake );
			void applyLinearImpulse( const b2Vec2& impulse, const b2Vec2& point, bool wake );
			void applyLinearImpulseToCenter( const b2Vec2& impulse, bool wake );
			void applyTorque( float32 torque, bool wake );
			void destroyFixture( b2Fixture* fixture );
			void dump();
			void getMassData( b2MassData* data ) const;
			void resetMassData();
			void setAngularDamping( float32 angularDamping );
			void setAngularVelocity( float32 omega );
			void setAwake( bool flag );
			void setBullet( bool flag );
			void setFixedRotation( bool flag );
			void setFixtureDefComponentActive( FixtureDefComponent* fixtureDefComponent, bool active );
			void setFixtureDefComponentEnabled( FixtureDefComponent* fixtureDefComponent, bool enabled );
			void setGravityScale( float32 scale );
			void setMassData( const b2MassData* data );
			void setLinearDamping( float32 linearDamping );
			void setLinearVelocity( const b2Vec2& v );
			void setLocalPosition( b2Vec2 position ) override;
			void setSleepingAllowed( bool flag );
			void setTransform( const b2Vec2& position, float32 angle );
			void setType( b2BodyType type );

			bool isAwake() const;
			bool isBodyActive() const;
			bool isBullet() const;
			bool isFixedRotation() const;
			bool isSleepingAllowed() const;

			float32 getAngle() const;
			float32 getAngleInRadians() const;
			float32 getAngularDamping() const;
			float32 getAngularVelocity() const;
			float32 getGravityScale() const;
			float32 getInertia() const;
			float32 getLinearDamping() const;
			float32 getMass() const;

			b2Vec2 getLinearVelocityFromLocalPoint( const b2Vec2& localPoint ) const;
			b2Vec2 getLinearVelocityFromWorldPoint( const b2Vec2& worldPoint ) const;
			b2Vec2 getLocalPoint( const b2Vec2& worldPoint ) const;
			b2Vec2 getLocalVector( const b2Vec2& worldVector ) const;
			b2Vec2 getWorldPoint( const b2Vec2& localPoint ) const;
			b2Vec2 getWorldVector( const b2Vec2& localVector ) const;

			const b2Vec2& getLocalCenter() const;
			const b2Vec2& getLinearVelocity() const;
			const b2Vec2& getPosition() const;
			const b2Vec2& getWorldCenter() const;

			b2Fixture* createFixture( const b2FixtureDef* def );
			b2Fixture* createFixture( const b2Shape* shape, float32 density );
			b2Fixture* getFixtureList();

			const b2Fixture* getFixtureList() const;

			const b2Transform& getTransform() const;

			b2BodyType getType() const;

			b2JointEdge* getJointList();

			const b2JointEdge* getJointList() const;

			b2ContactEdge* getContactList();

			const b2ContactEdge* getContactList() const;

			b2Body* getNext();

			const b2Body* getNext() const;

			b2World* getWorld();

			const b2World* getWorld() const;
		};
	}
}

#endif /* Comp2D_HEADERS_COMPONENTS_PHYSICSTRANSFORMCOMPONENT_H_ */
