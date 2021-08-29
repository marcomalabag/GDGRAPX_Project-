#pragma once
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int test = 0;
double Xposition, Yposition;
glm::mat4 transformMatrix;
float XLast, YLast;
bool FirstPositions = true;
float xOffSet, yOffSet;
float ScaleX, ScaleY;
float Rotate;
float TransformX, TransformY;
float PreviosX, PreviousY;
float XMousePosition, YMousePosition;


void SetLastPositions(float xlast, float ylast) {
    XLast = xlast;
    YLast = ylast;
}

void setRotate(float rotate) {
    Rotate = rotate;
}

void setTransform(float transformX, float transformY){
    TransformX = transformX;
    TransformY = transformY;
}

void setScale(float scaleX, float scaleY) {
    ScaleX = scaleX;
    ScaleY = scaleY;
}

float getScaleX() {
    return ScaleX;
}

float getScaleY() {
    return ScaleY;
}

float getTransformX() {
    return TransformX;
}

float getTransformY() {
    return TransformY;
}

float getRotate() {
    return Rotate;
}

glm::mat4 getTransformMatrix() {
    return transformMatrix;
}

