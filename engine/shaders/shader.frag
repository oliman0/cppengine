#version 430 core

out vec4 FragColour;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 Colour;
} fs_in;

struct Material {
    sampler2D diffuseT;
    sampler2D specularT;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float shininess;
}; 

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform bool usingTexture;
uniform bool fullBright;

const int MAX_POINT_LIGHTS = 10;

uniform Material material;
uniform Light pointLights[MAX_POINT_LIGHTS];
uniform int numOfLights;

uniform vec3 viewPos;

const float NOISE_GRANULARITY = 0.5/255.0;

float ditherRand(vec2 f) {
   return fract(sin(dot(f, vec2(12.9898,78.233))) * 43758.5453f);
}

vec3 CalculatePointLight(Light plight, Material mat, vec3 fragPosition, vec3 normal, vec4 valueD, vec4 valueS) {
    vec3 valueDgc = vec3(pow(valueD.r, 1/2.2), pow(valueD.g, 1/2.2), pow(valueD.b, 1/2.2));
    vec3 valueSgc = vec3(pow(valueS.r, 1/2.2), pow(valueS.g, 1/2.2), pow(valueS.b, 1/2.2));

    // ambient
    vec3 ambient = plight.ambient * mat.ambient * valueDgc;
  	
    // diffuse 
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(plight.position - fragPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = plight.diffuse * diff * mat.diffuse * valueDgc;  
    
    // specular
    vec3 viewDir = normalize(viewPos - fragPosition);
    vec3 reflectDir = reflect(-lightDir, norm);  
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(norm, halfwayDir), 0.0), mat.shininess);
    vec3 specular = plight.specular * valueSgc * mat.specular * spec;

    float distance    = length(plight.position - fragPosition);
    float attenuation = 1.0 / (plight.constant + pow(plight.linear * distance, 2.2) + pow(plight.quadratic * (distance * distance), 2.2));  

    ambient *= attenuation;  
    diffuse *= attenuation;
    specular *= attenuation; 

    return ambient + diffuse + specular;
}

void main() {
    vec4 valueD = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 valueS = vec4(0.0, 0.0, 0.0, 1.0);

    vec3 outValue = vec3(0.0);

    // Load Colour Data
    if (usingTexture) {
        valueD = fs_in.Colour * texture(material.diffuseT, fs_in.TexCoords);
        valueS = fs_in.Colour * texture(material.specularT, fs_in.TexCoords);
    }
    else if (!usingTexture) {
        valueD = fs_in.Colour;
        valueS = fs_in.Colour;
    }

    // Apply Lighting
    if (!fullBright) {
        for (int i = 0; i < numOfLights && numOfLights <= MAX_POINT_LIGHTS; i++) {
            outValue += CalculatePointLight(pointLights[i], material, fs_in.FragPos, fs_in.Normal, valueD, valueS);
        }
    }
    else {
        outValue += vec3(pow(valueD.r, 1/2.2), pow(valueD.g, 1/2.2), pow(valueD.b, 1/2.2));
    }

    // Apply Dithering
    outValue += vec3(mix(-NOISE_GRANULARITY, NOISE_GRANULARITY, ditherRand(gl_FragCoord.xy / vec2(1920.0, 1080.0))));
    
    FragColour = vec4(outValue, valueD.a);
}