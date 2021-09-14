#pragma once
#include "main.h"

ObjData BrandenburgGateData;

void InitializeBrandenburgGate() {
	LoadObjFile(&BrandenburgGateData, "BrandenburgGate/BrandenburgGate.obj");

	GLfloat GateOffsets[] = { -3.0f, 0.1f, -1.5f };

	LoadObjToMemory(
		&BrandenburgGateData,
		1.0f,
		GateOffsets
	);
}

void BindBrandenburgGate() {
	glBindVertexArray(BrandenburgGateData.vaoId);
}

void DrawBrandenburgGate() {
	glActiveTexture(GL_TEXTURE0);
	GLuint backPackTexture = BrandenburgGateData.textures[BrandenburgGateData.materials[0].diffuse_texname];
	glBindTexture(GL_TEXTURE_2D, backPackTexture);

	glActiveTexture(GL_TEXTURE1);
	GLuint normalTexture = BrandenburgGateData.textures[BrandenburgGateData.materials[0].bump_texname];
	glBindTexture(GL_TEXTURE_2D, normalTexture);

	glActiveTexture(GL_TEXTURE3);
	GLuint SecondTexture = BrandenburgGateData.textures[BrandenburgGateData.materials[1].diffuse_texname];
	glBindTexture(GL_TEXTURE_2D, SecondTexture);

	glActiveTexture(GL_TEXTURE4);
	GLuint SecondnormalTexture = BrandenburgGateData.textures[BrandenburgGateData.materials[1].bump_texname];
	glBindTexture(GL_TEXTURE_2D, SecondnormalTexture);



	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawElements(GL_TRIANGLES, BrandenburgGateData.numFaces, GL_UNSIGNED_INT, (void*)0);
	//glDisable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, 0);
}