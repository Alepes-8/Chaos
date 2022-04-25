#include "Camera.h"



void GameEngine::Camera::at(float x, float y, float z)
{
	_at = { x ,y ,z };
}

void GameEngine::Camera::eye(float x, float y, float z)
{
	_eye = { x, y, z };
}

void GameEngine::Camera::up(float x, float y, float z)
{
	_up = { x, y, z };
}

void GameEngine::Camera::translate(float x, float y, float z)
{
	_at.x += x;
	_at.y += y;
	_at.z += z;
	_eye.x += x;
	_eye.y += y;
	_eye.z += z;
}

void GameEngine::Camera::reset()
{
	at(0, 0, 0);
	eye(0, 0, 10);
	up(0, 1, 0);
	camera_speed = 0.5f;
}

void GameEngine::Camera::listenEvent(GameEngine::InputManager* im)
{
	//moves the camera with the arrows
	if (im->Keydown(SDL_SCANCODE_RIGHT)) {
		std::cout << "x positve" << std::endl;
		//std::cout << _at.x << _at.y << _at.z << std::endl;
		this->translate(-camera_speed, 0.0f, 0.0f);
	}
	else if (im->Keydown(SDL_SCANCODE_LEFT)) {
		std::cout << "x positve" << std::endl;
		this->translate(camera_speed, 0.0f, 0.0f);
	}
	else if (im->Keydown(SDL_SCANCODE_UP)) {
		std::cout << "y positive" << std::endl;
		this->translate(0.0f, camera_speed, 0.0f);
	}
	else if (im->Keydown(SDL_SCANCODE_DOWN)) {
		std::cout << "y negative" << std::endl;
		this->translate(0.0f, -camera_speed, 0.0f);
	}
	else if (im->Keydown(SDL_SCANCODE_KP_1)) {
		std::cout << "z positive" << std::endl;
		this->translate(0.0f, 0.0f, +camera_speed);
	}
	else if (im->Keydown(SDL_SCANCODE_KP_7)) {
		std::cout << "z negative" << std::endl;
		this->translate(0.0f, 0.0f, -camera_speed);
	}
	else if (im->Keydown(SDL_SCANCODE_KP_8)) {
		_up.y += camera_speed;
	}
	else if (im->Keydown(SDL_SCANCODE_KP_2)) {
		_up.y -= camera_speed;
	}
	else if (im->KeyPressed(SDL_SCANCODE_KP_0)) {
		std::cout << "cam reset" << std::endl;
		this->reset();
	}
	else if (im->KeyPressed(SDL_SCANCODE_KP_9)) {
		std::cout << "speed : " << camera_speed << std::endl;
		camera_speed += 0.1f;
	}
	else if (im->KeyPressed(SDL_SCANCODE_KP_3)) {
		std::cout << "speed : " << camera_speed << std::endl;
		camera_speed -= 0.1f;
	}
}


void GameEngine::Camera::update(GameEngine::InputManager* im, int view_port_id, float screen_width, float screen_height)
{
	
	this->listenEvent(im);

	bx::mtxLookAt(_view, _eye, _at, _up);

	bx::mtxProj(_proj,
		60.0f,
		float(screen_width) / float(screen_height),
		0.1f, 100.0f,
		bgfx::getCaps()->homogeneousDepth);

	bgfx::setViewTransform(0, _view, _proj);

	bgfx::setViewRect(view_port_id, 0, 0,
		screen_width,
		screen_height);

	
	bgfx::touch(0);
}
