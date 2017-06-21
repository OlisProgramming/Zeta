#pragma once

namespace zeta {
	namespace physics {

		class AABB;

		enum class PhysObjectType {
			AABB
		};

		class PhysObject {

		public:
			virtual bool collide(const PhysObject& other) const;
			virtual const PhysObjectType getType() const = 0;

			static bool collide(const PhysObject& a, const PhysObject& b);
			static bool collide(const AABB& a, const AABB& b);
		};
	}
}