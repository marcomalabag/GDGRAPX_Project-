#version 330 core
in vec3 u_color;
out vec4 FragColor;
in vec3 FragPos;
in vec2 UV;
in vec3 Normal;
in vec3 Tangent;
in vec3 Bitangent;
uniform sampler2D texture_diffuse;
uniform sampler2D night_diffuse;



uniform vec3 u_light_post;
uniform vec3 u_camera_pos;
uniform vec3 u_ambient_color;

float attenuate(float value, float maximum) {
	float clampedValue = min(value, maximum);
	return 1.0 / (pow(5 * clampedValue / maximum, 2) + 1);
}


void main()
{

	vec3 lightVector = normalize(u_light_post - FragPos);

	float distance = length(u_light_post - FragPos);
	//float gradient = attenuate(distance, 100.0);

	vec3 lightColor = vec3(1.0, 1.0, 1.0);

	float specularStrength = 0.3;
	vec3 viewDir = normalize(u_camera_pos - FragPos);

	///phong shading
	vec3 reflectDir = reflect(-lightVector, Normal);

	float spec = pow(max(dot(reflectDir, viewDir), 0.0), 4);

	//blinn phong
	//float spec = 0.0;


	vec3 specular = specularStrength * spec * lightColor;
	float NdotL = max(dot(Normal, lightVector), 0.0);
	vec3 diffuse = vec3(NdotL) * lightColor;
	vec3 ambient = u_ambient_color * lightColor;


	FragColor = vec4(ambient + (diffuse + specular), 1.0) * texture(texture_diffuse, UV)  +  texture(night_diffuse, UV) * (1.0 - NdotL);


}