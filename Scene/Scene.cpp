#include "Scene.hpp"

#include <string>
#include <stdexcept>
#ifdef _DEBUG
#include <iostream>
#endif

namespace loser_scene{


	void Scene::zoomCamera(const loser_math::RealNumber x) noexcept{
		main_camera_.zoom(x);
	}

	void Scene::moveCamera(const loser_math::RealNumber x, const loser_math::RealNumber y) noexcept{
		main_camera_.move(x, y);
	}
	void Scene::moveViewPointVertical(const loser_math::RealNumber y) noexcept{
		main_camera_.moveViewPointVertical(y);
	}
	void Scene::moveViewPointHorizontal(const loser_math::RealNumber x, const loser_math::RealNumber y) noexcept{
		main_camera_.moveViewPointHorizontal(x, y);
	}

	void Scene::computeProjectionMatrix(const loser_math::RealNumber width, const loser_math::RealNumber height) noexcept{
		main_camera_.computeProjectionMatrix(width / height);
		return;
	}

}