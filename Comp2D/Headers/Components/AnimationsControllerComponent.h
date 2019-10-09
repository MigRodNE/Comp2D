/* AnimationsControllerComponent.h -- 'Comp2D' Game Engine 'AnimationsControllerComponent' class header file
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

#ifndef Comp2D_HEADERS_COMPONENTS_ANIMATIONSCONTROLLERCOMPONENT_H_
#define Comp2D_HEADERS_COMPONENTS_ANIMATIONSCONTROLLERCOMPONENT_H_

#include <SDL.h>

#include "Comp2D/Headers/Animations/AnimationsController.h"
#include "Comp2D/Headers/Components/Component.h"
#include "Comp2D/Headers/Components/SpriteComponent.h"
#include "Comp2D/Headers/Objects/GameObject.h"
#include "Comp2D/Headers/Resources/GenericResource.h"

namespace Comp2D
{
	namespace Components
	{
		class AnimationsControllerComponent : public Component
		{
		protected:
			bool m_pausable;

			Comp2D::Components::SpriteComponent* m_animationsSpriteComponent;

			Comp2D::Resources::GenericResource<Comp2D::Animations::AnimationsController>* m_animationsControllerResource;

		public:
			bool playStartingAnimationOnInitializeState;

			AnimationsControllerComponent
			(
				unsigned int id,
				Comp2D::Objects::GameObject* gameObject,
				Comp2D::Resources::GenericResource<Comp2D::Animations::AnimationsController>* animationsControllerResource = nullptr,
				bool playStartingAnimationOnInitializeState = true,
				bool pausable = true
			);

			~AnimationsControllerComponent();

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

			void setAnimationsControllerResource( Comp2D::Resources::GenericResource<Comp2D::Animations::AnimationsController>* animationsControllerResource );
			void setAnimationsSpriteComponent( Comp2D::Components::SpriteComponent* animationsSpriteComponent );
			void setPausable( bool pausable );
			void update( Uint32 currentTime );

			bool isPausable() const;

			Comp2D::Animations::AnimationsController* getAnimationsController() const;

			Comp2D::Resources::GenericResource<Comp2D::Animations::AnimationsController>* getAnimationsControllerResource() const;

			const Comp2D::Components::SpriteComponent& getAnimationsSpriteComponent() const;
		};
	}
}

#endif /* Comp2D_HEADERS_COMPONENTS_ANIMATIONSCONTROLLERCOMPONENT_H_ */
