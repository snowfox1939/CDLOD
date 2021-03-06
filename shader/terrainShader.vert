#version 150

in vec3 position;

uniform mat4 projection;
uniform mat4 view;
uniform vec3 translation;
uniform float scale;
uniform float range;
uniform vec3 cameraPos;
uniform sampler2D myTextureSampler;
uniform vec3 gridDim;

out vec4 fPosition;
out vec3 fWorldPosition;
out float fDist;
out vec3 fNormal;
out vec2 screenPos;

vec2 morphVertex( vec2 gridPos, vec2 worldPos, float morph) {
	vec2 fracPart = fract(gridPos * gridDim.xy * 0.5) * 2.0 / gridDim.xy;
	return worldPos - fracPart * scale * morph;
}

float getHeight(vec2 v) {
	return 20.0*(texture( myTextureSampler, v/100.0).r - 0.5);
}

void main(void)
{
	float morphStart = 0.0;
	float morphEnd = 0.25;

	fWorldPosition = scale*position + translation;
	float height = getHeight(fWorldPosition.xz);
	fWorldPosition.y = height; 
	float dist = distance(cameraPos, fWorldPosition);
	float nextlevel_thresh = ((range-dist)/scale*gridDim.x/32.0); //positive if within range
	float rangeDist = 1.0 - smoothstep(morphStart, morphEnd, nextlevel_thresh);

	float morphVal = rangeDist;
	fWorldPosition.xz = morphVertex(position.xz, fWorldPosition.xz, morphVal);
	height = getHeight(fWorldPosition.xz);
	
	// * 0.5*(sin(fWorldPosition.x) + sin(fWorldPosition.z));
	//height!
	fWorldPosition.y = height; 

    fPosition = view * vec4(fWorldPosition,1.0);

    fDist = dist;
    gl_Position = projection * fPosition;
    screenPos = gl_Position.xy;
}