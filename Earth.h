#pragma once
#pragma once
#include "main.h"

ObjData EarthObjData;

void InitializeEarth() {
	
	LoadObjFile(&EarthObjData, "backpack/backpack.obj");
	GLfloat bunnyOffsets[] = { 0.0f, 0.0f, -1.5f };

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

	glActiveTexture(GL_TEXTURE1);
	GLuint normalTexture = EarthObjData.textures[EarthObjData.materials[0].bump_texname];
	glBindTexture(GL_TEXTURE_2D, normalTexture);

	

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawElements(GL_TRIANGLES, EarthObjData.numFaces, GL_UNSIGNED_INT, (void*)0);
	//glDisable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, 0);


}