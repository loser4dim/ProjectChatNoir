#pragma once

namespace loser_renderer{


	class Renderer{


	public:
		Renderer() = default;

		Renderer(const Renderer&) = delete;
		Renderer(Renderer&&) = delete;

		Renderer& operator=(const Renderer&) = delete;
		Renderer& operator=(Renderer&&) = delete;


		~Renderer() = default;


	};
}
