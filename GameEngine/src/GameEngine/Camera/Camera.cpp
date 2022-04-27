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

void GameEngine::Camera::translate_direction(GameEngine::Direction direction, float speed)
{
	Vector3 dir = { 0, 0, 0 };
	Vector3 gaze_dir = Vector3 (_eye.x - _at.x, _eye.y - _at.y, _eye.z - _at.z ).Normalized();
	Vector3 ortho_gaze_dir = gaze_dir.Vectorial_product(Vector3(_up.x, _up.y, _up.z )).Normalized();
	switch (direction) {
	case LEFT:
		dir = ortho_gaze_dir * -speed;
		_at = { _at.x + dir.x, _at.y + dir.y, _at.z + dir.z };
		break;
	case RIGHT:
		dir = ortho_gaze_dir * speed;
		_at = { _at.x + dir.x, _at.y + dir.y, _at.z + dir.z };
		break;
	case UP:
		dir = Vector3 { _up.x, _up.y, _up.z}.Normalized() * speed;
		_at = { _at.x + dir.x, _at.y + dir.y, _at.z + dir.z };
		break;
	case DOWN:
		dir = Vector3 { _up.x, _up.y, _up.z }.Normalized() * -speed;
		_at = { _at.x + dir.x, _at.y + dir.y, _at.z + dir.z };
		break;
	case FORWARD:
		dir = gaze_dir * speed;
		break;
	case BACKWARD:
		dir = gaze_dir * -speed;
		break;
	default:
		break;
	}

	
	_eye = { _eye.x + dir.x, _eye.y + dir.y, _eye.z + dir.z };
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
	//moves the camera with the keyboard

	//translation riht - right arrow
	if (im->Keydown(SDL_SCANCODE_RIGHT)) {
		std::cout << "x positve" << std::endl;
		this->translate_direction(RIGHT, camera_speed);
	}

	//translation left - left arrow
	else if (im->Keydown(SDL_SCANCODE_LEFT)) {
		std::cout << "x positve" << std::endl;
		this->translate_direction(LEFT, camera_speed);
	}

	//translation up - up arrow
	else if (im->Keydown(SDL_SCANCODE_UP)) {
		std::cout << "y positive" << std::endl;
		this->translate_direction(UP, camera_speed);
	}

	//translation down - down arrow
	else if (im->Keydown(SDL_SCANCODE_DOWN)) {
		std::cout << "y negative" << std::endl;
		this->translate_direction(DOWN, camera_speed);
	}

	//translation backward - keypad 1
	else if (im->Keydown(SDL_SCANCODE_KP_1)) {
		std::cout << "z positive" << std::endl;
		this->translate_direction(FORWARD, camera_speed);
	}

	//translation forward - keypad 7
	else if (im->Keydown(SDL_SCANCODE_KP_7)) {
		std::cout << "z negative" << std::endl;
		this->translate_direction(Direction::BACKWARD, camera_speed);
	}

	//rotates left - keypad 4
	else if (im->Keydown(SDL_SCANCODE_KP_4)) {
		float teta;
		float r = sqrt(pow((_eye.x - _at.x), 2) + pow((_eye.z - _at.z), 2));
		if (_eye.z - _at.z > 0) {
			teta = acos((_eye.x - _at.x) / r);
		}
		else {
			teta = -acos((_eye.x - _at.x) / r);
		}

		teta += (camera_speed / 10);

		_eye.x = r * cos(teta) + _at.x;
		_eye.z = r * sin(teta) + _at.z;	
	}

	//rotates right - keypad 6
	else if (im->Keydown(SDL_SCANCODE_KP_6)) {
		float teta;
		float r = sqrt(pow((_eye.x - _at.x), 2) + pow((_eye.z - _at.z), 2));
		if (_eye.z - _at.z > 0) {
			teta = acos((_eye.x - _at.x) / r);
		}
		else {
			teta = -acos((_eye.x - _at.x) / r);
		}

		teta -= (camera_speed / 10);

		_eye.x = r * cos(teta) + _at.x;
		_eye.z = r * sin(teta) + _at.z;
	}

	//rotates forward - keypad 8 -> NOT WORKING
	else if (im->Keydown(SDL_SCANCODE_KP_8)) {
		float teta;
		float r = sqrt(pow((_eye.y - _at.y), 2) + pow((_eye.z - _at.z), 2));
		if (_eye.z - _at.z > 0) {
			teta = acos((_eye.y - _at.y) / r);
		}
		else {
			teta = -acos((_eye.y - _at.y) / r);
		}

		teta -= (camera_speed / 10);

		_eye.y = r * cos(teta) + _at.y;
		_eye.z = r * sin(teta) + _at.z;

	
		if (_eye.z - _at.z > 0) {
			_up.y = 1;
		}
		else {
			teta = -acos((_eye.y - _at.y) / r);
			_up.y = -1;
		}
	}

	//rotates backward - keypad 2 -> NOT WORKING
	else if (im->Keydown(SDL_SCANCODE_KP_2)) {
		float teta;
		float r = sqrt(pow((_eye.y - _at.y), 2) + pow((_eye.z - _at.z), 2));
		if (_eye.z - _at.z > 0) {
			teta = acos((_eye.y - _at.y) / r);
		}
		else {
			teta = -acos((_eye.y - _at.y) / r);
		}

		teta += (camera_speed / 10);

		_eye.y = r * cos(teta) + _at.y;
		_eye.z = r * sin(teta) + _at.z;

		if (_eye.z - _at.z > 0) {
			_up.y = 1;
		}
		else {
			teta = -acos((_eye.y - _at.y) / r);
			_up.y = -1;
		}

	}

	//reset camera - keypad 0
	else if (im->KeyPressed(SDL_SCANCODE_KP_0)) {
		std::cout << "cam reset" << std::endl;
		this->reset();
	}

	//increase camera speed - keypad 9
	else if (im->KeyPressed(SDL_SCANCODE_KP_9)) {
		std::cout << "speed : " << camera_speed << std::endl;
		camera_speed += 0.1f;
	}

	//decrease camera speed - keypad 3
	else if (im->KeyPressed(SDL_SCANCODE_KP_3)) {
		std::cout << "speed : " << camera_speed << std::endl;
		camera_speed -= 0.1f;
	}
	else if (im->KeyPressed(SDL_SCANCODE_KP_0)) {
		std::cout << "cam reset" << std::endl;
		this->reset();
	}
}


void GameEngine::Camera::Update(GameEngine::InputManager* im, int view_port_id, float screen_width, float screen_height)
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
