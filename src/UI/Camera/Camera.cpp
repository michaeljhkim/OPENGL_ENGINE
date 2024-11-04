#include <Headers/Camera.hpp>
#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtx/rotate_vector.hpp>

//Default values of where camera should be in world
//TEMPORARY VALUES - NEEDS TO CHANGE ONCE WE STOP USING 0.obj AS TESTING
Camera::Camera(){
    //location of camera in world
    mEye = glm::vec3(20.0f, 100.0f, 200.0f);

    //Direction which camera is facing
    //must subtract mEye for default value because mEye gets added to mViewDirection
    mViewDirection = glm::vec3(0.0f, 110.0f, -1.0f) - mEye;
    
    //For finding the rightside up
    mUpVector = glm::vec3(0.0f, 1.0f, 0.0f);

    //Holding previous frame's mouse position
    mOldMousePosition = glm::vec2(0.0f, 0.0f);

}

glm::mat4 Camera::GetViewMatrix() const{
    //return glm::lookAt(glm::vec3(20.0f, 100.0f, 200.0f), glm::vec3(0.0f, 110.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    return glm::lookAt(mEye, mEye+mViewDirection, mUpVector);
}



void Camera::MouseLook(int mouseX, int mouseY){
    //float mX = static_cast<float>(mouseX);
    //float mY = static_cast<float>(mouseY);
    float mX_Sensitivity = 0.05f;
    float mY_Sensitivity = 0.03f;
    glm::vec2 CurrentMousePosition(mouseX*mX_Sensitivity, mouseY*mY_Sensitivity); 

    //makes sure that mOldMousePosition does not start null, and instead has a beginning
    static bool firstLook = true;
    if (firstLook) {
        mOldMousePosition = CurrentMousePosition;
        firstLook = false;
    }
    glm::vec2 mouseDelta = mOldMousePosition - CurrentMousePosition; 

    // Convert mViewDirection to a 4D vector, apply rotation, and convert back to 3D
    // Rotation around the y-axis (yaw) - horizontal movement
    glm::mat4 yawRotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(mouseDelta.x), mUpVector);
    mViewDirection = glm::vec3(yawRotationMatrix * glm::vec4(mViewDirection, 0.0f));

    // Rotation around the x-axis (pitch) - vertical movement
    glm::vec3 rightVector = glm::normalize(glm::cross(mViewDirection, mUpVector));
    glm::mat4 pitchRotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(-mouseDelta.y), -rightVector);
    mViewDirection = glm::vec3(pitchRotationMatrix * glm::vec4(mViewDirection, 0.0f));

    mOldMousePosition = CurrentMousePosition;
    std::cout << mViewDirection.x << ", " << mViewDirection.y << ", " << mViewDirection.z << std::endl;
    //std::cout << mouseX << std::endl;
}


//Names indicate which direction the camera moves
void Camera::MoveForward(float speed) {
    mEye += (mViewDirection * speed);
}
void Camera::MoveBack(float speed) {
    mEye -= (mViewDirection * speed);
}
void Camera::MoveLeft(float speed) {
    glm::vec3 rightVector = glm::cross(mViewDirection, mUpVector);
    mEye -= (rightVector * speed);
}
void Camera::MoveRight(float speed) {
    glm::vec3 rightVector = glm::cross(mViewDirection, mUpVector);
    mEye += (rightVector * speed);
}
