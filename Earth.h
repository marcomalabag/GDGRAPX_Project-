#pragma once
#pragma once
#include "main.h"

ObjData EarthObjData;

void InitializeEarth() {
	
	LoadObjFile(&EarthObjData, "earth/Earth.obj");
	GLfloat bunnyOffsets[] = { 0.0f, 0.0f, 0.0f };

	LoadObjToMemory(
		&EarthObjData,
		1.0f,
		bunnyOffsets

	);
}

void BindEarthArray() {
	glBindVertexArray(EarthObjData.vaoId);
}

void DrawEarth() {

	glActiveTexture(GL_TEXTURE0);
	GLuint backPackTexture = EarthObjData.textures[EarthObjData.materials[0].diffuse_texname];
	glBindTexture(GL_TEXTURE_2D, backPackTexture);

	glDrawElements(GL_TRIANGLES, EarthObjData.numFaces, GL_UNSIGNED_INT, (void*)0);

	glBindTexture(GL_TEXTURE_2D, 0);


}