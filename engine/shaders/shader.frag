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

struct PointLight {
    vec3 position;

    vec3 diffuse;
    vec3 specular;

    float intensity;

    float bias;
    float biasMin;
};

struct DirectionalLight {
    vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct SpotLight {
    vec3 position;
	vec3 direction;
	float innerCutOff;
    float outerCutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform bool usingTexture;
uniform bool fullBright;

uniform Material material;

const int MAX_POINT_LIGHTS = 10;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform int numOfPointLights;

uniform DirectionalLight directionalLight = DirectionalLight(vec3(0.0), vec3(0.0), vec3(0.0), vec3(0.0));

const int MAX_SPOT_LIGHTS = 10;
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];
uniform int numOfSpotLights;

uniform vec3 viewPos;

uniform samplerCube pointDepthMap;
uniform float farPlane;

const float NOISE_GRANULARITY = 0.5/255.0;

float ditherRand(vec2 f) {
   return fract(sin(dot(f, vec2(12.9898,78.233))) * 43758.5453f);
}

float CalculatePointLightShadow(PointLight light, vec3 fragPosition, vec3 normal) {
    // get vector between fragment position and light position
    vec3 fragToLight = fragPosition - light.position;
    // use the light to fragment vector to sample from the depth map    
    float closestDepth = texture(pointDepthMap, fragToLight).r;
    // it is currently in linear range between [0,1]. Re-transform back to original value
    closestDepth *= farPlane;
    // now get current linear depth as the length between the fragment and light position
    float currentDepth = length(fragToLight);
    // now test for shadows
    float bias = max(light.bias * (1.0 - dot(normal, fragToLight)), light.biasMin);
    float shadow = currentDepth -  bias > closestDepth ? 1.0 : 0.0;

    return shadow;
}

vec3 CalculatePointLight(PointLight light, Material mat, vec3 fragPosition, vec3 normal, vec4 valueD, vec4 valueS) {
    vec3 valueDgc = vec3(pow(valueD.r, 1/2.2), pow(valueD.g, 1/2.2), pow(valueD.b, 1/2.2));
    vec3 valueSgc = vec3(pow(valueS.r, 1/2.2), pow(valueS.g, 1/2.2), pow(valueS.b, 1/2.2));
  	
    // diffuse 
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * mat.diffuse * valueDgc;  
    
    // specular
    vec3 viewDir = normalize(viewPos - fragPosition);
    vec3 reflectDir = reflect(-lightDir, norm);  
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(norm, halfwayDir), 0.0), mat.shininess);
    vec3 specular = light.specular * valueSgc * mat.specular * spec;

    // attenuation
    float distance = length(light.position - fragPosition);
    float cosTerm = dot(light.position - fragPosition, normal);
    float attenuation = (1 / 3.1415926) * cosTerm * (light.intensity / (distance * distance));

    diffuse *= attenuation;
    specular *= attenuation; 

    float shadow = CalculatePointLightShadow(light, fragPosition, normal);
    return (1.0 - shadow) * (diffuse + specular);
}

vec3 CalculateDirectionalLight(DirectionalLight light, Material mat, vec3 fragPosition, vec3 normal, vec4 valueD, vec4 valueS) {
    vec3 lightDir = normalize(-light.direction);

    vec3 valueDgc = vec3(pow(valueD.r, 1/2.2), pow(valueD.g, 1/2.2), pow(valueD.b, 1/2.2));
    vec3 valueSgc = vec3(pow(valueS.r, 1/2.2), pow(valueS.g, 1/2.2), pow(valueS.b, 1/2.2));

    // ambient
    vec3 ambient = light.ambient * mat.ambient * valueDgc;
  	
    // diffuse 
    vec3 norm = normalize(normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * mat.diffuse * valueDgc;  
    
    // specular
    vec3 viewDir = normalize(viewPos - fragPosition);
    vec3 reflectDir = reflect(-lightDir, norm);  
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(norm, halfwayDir), 0.0), mat.shininess);
    vec3 specular = light.specular * valueSgc * mat.specular * spec;

    return ambient + diffuse + specular;
}

vec3 CalculateSpotLight(SpotLight light, Material mat, vec3 fragPosition, vec3 normal, vec4 valueD, vec4 valueS) {
    vec3 valueDgc = vec3(pow(valueD.r, 1/2.2), pow(valueD.g, 1/2.2), pow(valueD.b, 1/2.2));
    vec3 valueSgc = vec3(pow(valueS.r, 1/2.2), pow(valueS.g, 1/2.2), pow(valueS.b, 1/2.2));

    vec3 lightDir = normalize(light.position - fragPosition);

    // ambient
    vec3 ambient = light.ambient * mat.ambient * valueDgc;

    // diffuse 
    vec3 norm = normalize(normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * mat.diffuse * valueDgc;  
    
    // specular
    vec3 viewDir = normalize(viewPos - fragPosition);
    vec3 reflectDir = reflect(-lightDir, norm);  
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(norm, halfwayDir), 0.0), mat.shininess);
    vec3 specular = light.specular * valueSgc * mat.specular * spec;

    // light intensity and edge smoothing
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon   = light.innerCutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);    

    diffuse  *= intensity;
    specular *= intensity;

    // attenuation
    float distance    = length(light.position - fragPosition);
    float attenuation = 1.0 / (light.constant + pow(light.linear * distance, 2.2) + pow(light.quadratic * (distance * distance), 2.2));  

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation; 

    // extra dithering
    return (ambient + diffuse + specular) + vec3(mix(-NOISE_GRANULARITY / 2.0, NOISE_GRANULARITY / 2.0, ditherRand(gl_FragCoord.xy / vec2(1920.0, 1080.0))));;
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
        for (int i = 0; i < numOfPointLights && numOfPointLights <= MAX_POINT_LIGHTS; i++) {
            outValue += CalculatePointLight(pointLights[i], material, fs_in.FragPos, fs_in.Normal, valueD, valueS);
        }

        if (directionalLight.direction != vec3(0.0)) outValue += CalculateDirectionalLight(directionalLight, material, fs_in.FragPos, fs_in.Normal, valueD, valueS);

        for (int i = 0; i < numOfSpotLights && numOfSpotLights <= MAX_POINT_LIGHTS; i++) {
            outValue += CalculateSpotLight(spotLights[i], material, fs_in.FragPos, fs_in.Normal, valueD, valueS);
        }
    }
    else {
        outValue += vec3(pow(valueD.r, 1/2.2), pow(valueD.g, 1/2.2), pow(valueD.b, 1/2.2));
    }

    // Apply Dithering
    outValue += vec3(mix(-NOISE_GRANULARITY, NOISE_GRANULARITY, ditherRand(gl_FragCoord.xy / vec2(1920.0, 1080.0))));
    
    FragColour = vec4(outValue, valueD.a);
}