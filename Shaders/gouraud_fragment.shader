#version 330 core
in vec3 u_color;
out vec4 FragColor;
in vec2 UV;

uniform sampler2D texture_diffuse;
in vec4 vertexColor;
in vec3 o_normal;

uniform vec3 uniformColor;


void main()
{
	//FragColor = vec4(o_normal, 1.0);
	FragColor = vertexColor * texture(texture_diffuse, UV);
	//FragColor = texture(texture_diffuse, UV);
	//FragColor = vec4(vec3(1.0 - gl_FragCoord.z), 1.0) * texture(texture_diffuse, UV);
	//FragColor = vec4(u_color * uniformColor, 1.0);

}