#version 330 core
layout(location = 0)in vec3 a_pos;
layout(location = 1)in vec2 a_UV;
layout(location = 2)in vec3 a_normal;
uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;
uniform vec3 u_light_post;

out vec2 UV;
out vec3 o_normal;
out vec3 vertexColor;
void main()
{
	gl_Position = u_projection * u_view * u_model * vec4(a_pos, 1.0);
	//u_color = v_color;
	UV = a_UV;
	o_normal = a_normal;

	vec3 vertexPos = vec3(u_model * vec4(a_pos, 1.0));
	vec3 lightVector = normalize(u_light_post - vertexPos);

	vec3 diffuse = vec3(max(dot(a_normal, lightVector), 1.0));
	vertexColor = diffuse;

}