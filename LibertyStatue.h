#pragma once
#include "main.h"

ObjData LibertyStatueData;

void InitializeLibertyStatue() {
	LoadObjFile(&LibertyStatueData, "LibertyStatue/LibertStatue.obj");

	GLfloat StatueOffsets[] = { 0.0f, 0.0f, -1.5f };

	LoadObjToMemory(
		&LibertyStatueData,
		1.0f,
		StatueOffsets
	);
}

void BindLibertyStatueArray() {
	glBindVertexArray(LibertyStatueData.vaoId);
}

void DrawLibertyStatue() {
	glActiveTexture(GL_TEXTURE0);
	GLuint backPackTexture = LibertyStatueData.textures[LibertyStatueData.materials[0].diffuse_texname];
	glBindTexture(GL_TEXTURE_2D, backPackTexture);

	glActiveTexture(GL_TEXTURE1);
	GLuint normalTexture = LibertyStatueData.textures[LibertyStatueData.materials[0].bump_texname];
	glBindTexture(GL_TEXTURE_2D, normalTexture);



	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawElements(GL_TRIANGLES, LibertyStatueData.numFaces, GL_UNSIGNED_INT, (void*)0);
	//glDisable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, 0);
}