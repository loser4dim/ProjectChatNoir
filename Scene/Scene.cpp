#include "Scene.hpp"

#include <string>
#include <stdexcept>
#ifdef _DEBUG
#include <iostream>
#endif

namespace loser_scene{


	void Scene::zoomCamera(const std::float_t x) noexcept{
		main_camera_.zoom(x);
	}

	void Scene::moveCamera(const std::float_t x, const std::float_t y) noexcept{
		main_camera_.move(x, y);
	}
	void Scene::moveViewPointVertical(const std::float_t y) noexcept{
		main_camera_.moveViewPointVertical(y);
	}
	void Scene::moveViewPointHorizontal(const std::float_t x, const std::float_t y) noexcept{
		main_camera_.moveViewPointHorizontal(x, y);
	}

	void Scene::computeProjectionMatrix(const std::float_t width, const std::float_t height) noexcept{
		main_camera_.computeProjectionMatrix(width / height);
		return;
	}

}