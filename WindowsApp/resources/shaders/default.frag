#version 300 es
precision mediump float;

varying vec4 fragmentColor;
varying	vec2 fragmentTexture;

uniform sampler2D tex; 

//out vec4 finalColor; //this is the output color of the pixel

void main()
{
	//gl_FragColor = vec4(fragmentColor.x, fragmentColor.y, fragmentColor.z, fragmentColor.w);
	gl_FragColor = texture(tex, fragmentTexture);	
	//finalColor = texture(tex, Texcoord) * vec4(fragmentColor, 1.0);
}
