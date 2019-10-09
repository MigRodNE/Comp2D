/* FixtureDefComponent.h -- 'Comp2D' Game Engine 'FixtureDefComponent' class header file
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

#ifndef Comp2D_HEADERS_COMPONENTS_FIXTUREDEFCOMPONENT_H_
#define Comp2D_HEADERS_COMPONENTS_FIXTUREDEFCOMPONENT_H_

#include "Box2D/Collision/Shapes/b2Shape.h"
#include "Box2D/Common/b2Settings.h"
#include "Box2D/Dynamics/b2Fixture.h"

#include "Comp2D/Headers/Components/Component.h"
#include "Comp2D/Headers/Components/PhysicsTransformComponent.h"
#include "Comp2D/Headers/Objects/GameObject.h"

// OBS: LEMBRAR DE ADICIONAR/CONSTRUIR O PHYSICS COMPONENT ANTES DOS FIXTUREDEFCOMPONENTS!!!!

// TODO: Lidar com Deactivate e Disable do FixtureDefComponent
// TODO: Lidar com mudança de Scale do objeto (considerar mudança no scalingFactor)
// TODO: (OPCIONAL) Método para modificar/setar o m_fixture pelo FixtureDefComponent
// TODO: (OPCIONAL) Método para modificar/setar o m_fixtureDef pelo FixtureDefComponent

namespace Comp2D
{
	namespace Components
	{
		class FixtureDefComponent : public Component
		{
		protected:
			b2FixtureDef* m_fixtureDef;

			b2Fixture* m_fixture = nullptr;

			PhysicsTransformComponent* closestUpperPhysicsComponent = nullptr;

			PhysicsTransformComponent* getClosestUpperPhysicsComponent( Comp2D::Objects::GameObject* parentGameObject );

		public:
			enum class EFilterCategory
			{
				Default = 0x0002,
				Player = 0x0004,
				ScenarioObject = 0x0008,
				Ground = 0x0010,
				PassthroughGround = 0x0020,
				Wall = 0x0040,
				PassthroughWall = 0x0080
			};

			enum class EFilterMask
			{
				Default = 0xFFFF,
				Player = 0x00FE,
				ScenarioObject = 0x005E,
				Ground = 0x000E,
				PassthroughGround = 0x0006,
				Wall = 0x000E,
				PassthroughWall = 0x0006
			};

			enum class EFilterGroup
			{
				Default = 0,
				Player = 1,
				ScenarioObject = 2,
				Ground = -3,
				PassthroughGround = -4,
				Wall = -5,
				PassthroughWall = -6
			};

			FixtureDefComponent
			(
				unsigned int id,
				Comp2D::Objects::GameObject* gameObject,
				b2FixtureDef* fixtureDef
			);

			FixtureDefComponent
			(
				unsigned int id,
				Comp2D::Objects::GameObject* gameObject,
				b2Filter filter,
				b2Shape* shape = nullptr,
				float32 friction = 0.2f,
				float32 restitution = 0.0f,
				float32 density = 0.0f,
				bool isSensor = false
			);

			FixtureDefComponent
			(
				unsigned int id,
				Comp2D::Objects::GameObject* gameObject,
				b2Shape* shape = nullptr,
				float32 friction = 0.2f,
				float32 restitution = 0.0f,
				float32 density = 0.0f,
				bool isSensor = false,
				EFilterCategory filterCategory = EFilterCategory::Default,
				EFilterGroup filterGroup = EFilterGroup::Default
			);

			~FixtureDefComponent();

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

			void setFixture( b2Fixture* fixture );

			const b2FixtureDef* getFixtureDef() const;

			b2Fixture* getFixture() const;
		};
	}
}

#endif /* Comp2D_HEADERS_COMPONENTS_FIXTUREDEFCOMPONENT_H_ */
