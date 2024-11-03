#include <Headers/Camera.hpp>
#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtx/rotate_vector.hpp>


Camera::Camera(){
    mEye = glm::vec3(20.0f, 100.0f, 200.0f);
    mViewDirection = glm::vec3(0.0f, 110.0f, -1.0f);
    mUpVector = glm::vec3(0.0f, 1.0f, 0.0f);
    mOldMousePosition = glm::vec2(0.0f, 0.0f);

    mViewDirection -= mEye; 
}

glm::mat4 Camera::GetViewMatrix() const{
    //return glm::lookAt(glm::vec3(20.0f, 100.0f, 200.0f), glm::vec3(0.0f, 110.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    return glm::lookAt(mEye, mEye+mViewDirection, mUpVector);
}


// Convert mViewDirection to a 4D vector, apply rotation, and convert back to 3D
void Camera::MouseLook(int mouseX, int mouseY){
    //float mX = static_cast<float>(mouseX);
    //float mY = static_cast<float>(mouseY);
    glm::vec2 CurrentMousePosition(mouseX, mouseY); 

    static bool firstLook = true;
    if (firstLook) {
        mOldMousePosition = CurrentMousePosition;
        firstLook = false;
    }
    glm::vec2 mouseDelta = mOldMousePosition - CurrentMousePosition; 

    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(mouseDelta.x), mUpVector);
    mViewDirection = glm::vec3(rotationMatrix * glm::vec4(mViewDirection, 0.0f));
    mOldMousePosition = CurrentMousePosition;
    //std::cout << mViewDirection.x << ", " << mViewDirection.y << ", " << mViewDirection.z << std::endl;
    std::cout << mouseX << std::endl;
}

void Camera::MoveForward(float speed) {
    //std::cout << "Forward" << std::endl;
    mEye += (mViewDirection * speed);
}
void Camera::MoveBack(float speed) {
    mEye -= (mViewDirection * speed);
}
void Camera::MoveLeft(float speed) {
    //mEye.x -= speed;
}
void Camera::MoveRight(float speed) {
    //mEye.x += speed;
}
