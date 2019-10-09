/* ScreenSpaceTransformComponent.h -- 'Comp2D' Game Engine 'ScreenSpaceTransformComponent' class header file
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

#ifndef Comp2D_HEADERS_COMPONENTS_SCREENSPACETRANSFORMCOMPONENT_H_
#define Comp2D_HEADERS_COMPONENTS_SCREENSPACETRANSFORMCOMPONENT_H_

#include "Box2D/Common/b2Math.h"
#include "Box2D/Common/b2Settings.h"

#include "Comp2D/Headers/Components/TransformComponent.h"
#include "Comp2D/Headers/Objects/GameObject.h"
#include "Comp2D/Headers/Utilities/Vector2D.h"

// TODO: Realizar caminho inverso do cálculo do m_localPosition em
//		 - updateLocalPosition
//		 - updateLocalRotation
//		 - updateLocalScale
//		 - updateLocalTransform
// TODO: Lidar com ativação/desativação de TransformComponent
// TODO: Lidar com enable/disable de TransformComponent
// TODO: (OPCIONAL) setLocalTransform
// TODO: (OPCIONAL) setWorldTransform

namespace Comp2D
{
	namespace Components
	{
		class ScreenSpaceTransformComponent : public TransformComponent
		{
		protected:
			void updateTransform() override;

		public:
			ScreenSpaceTransformComponent
			(
				unsigned int id,
				Comp2D::Objects::GameObject* gameObject,
				b2Vec2 localPosition = { 0.0f, 0.0f },
				float32 localRotation = 0.0f,
				b2Vec2 localScale = { 1.0f, 1.0f }
			);

			~ScreenSpaceTransformComponent();

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
		};
	}
}

#endif /* Comp2D_HEADERS_COMPONENTS_SCREENSPACETRANSFORMCOMPONENT_H_ */
