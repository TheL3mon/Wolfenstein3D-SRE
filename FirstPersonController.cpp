#include "FirstPersonController.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtx/transform.hpp"

using namespace sre;
using namespace glm;


FirstPersonController::FirstPersonController(sre::Camera * camera)
:camera(camera)
{
    camera->setPerspectiveProjection(45,0.1f,1000);
    position = vec3(0,0,0);
    at = vec3(0, 0, -1);
    fwd = false;
    bwd = false;
    left = false;
    right = false;
    xrel = 0;
}

void FirstPersonController::update(float deltaTime){
    float rotationRad = glm::radians(rotation);
    at = rotateY(vec3(0,0,-1), rotationRad);

    camera->lookAt(position, position+at, vec3(0, 1, 0));

    if (fwd)
    {
        position += (rotateY(vec3(0, 0, -5), rotationRad)) * deltaTime;
    }
    if (bwd)
    {
        position += (rotateY(vec3(0, 0, 5), rotationRad)) * deltaTime;
    }
    if (left)
    {
        position += (rotateY(vec3(-5, 0, 0), rotationRad)) * deltaTime;
    }
    if (right)
    {
        position += (rotateY(vec3(5, 0, 0), rotationRad)) * deltaTime;
    }
}

void FirstPersonController::onKey(SDL_Event &event) {
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_w) {
        fwd = true;
    }
    else
    {
        fwd = false;
    }

    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_s) {
        bwd = true;
    }
    else
    {
        bwd = false;
    }

    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_a) {
        left = true;
    }
    else
    {
        left = false;
    }

    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_d) {
        right = true;
    }
    else
    {
        right = false;
    }

    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
        exit(0);
    }
}

void FirstPersonController::onMouse(SDL_Event &event) {
    if (event.motion.xrel <= 0) {
        rotation += 1;
    }
    else if (event.motion.xrel >= 0) {
        rotation -= 1;
    }
}

void FirstPersonController::setInitialPosition(glm::vec2 position, float rotation) {
    this->position = glm::vec3(position.x,0,position.y);
    this->rotation = rotation;
}
