/** *********************************************************************** **/
/** *********************************************************************** **/
/**     Created by:     Ruan (Baggins) Luies 23511354                       **/
/**     email:          23511354@nwu.ac.za                                  **/
/**     Project name:   Virtual Concierge Creator And Management System     **/
/**     File Name:      mainFrag.frag                                       **/
/**     From Date:      2015/02/24                                          **/
/**     To Date:        2015/10/01                                          **/
/** **********************************************************************  **/
/** *********************************************************************** **/
uniform lowp float t;
varying highp vec4 posi;
//! [0]
uniform sampler2D texture;
uniform sampler2D normaltexture;

// constants
//uniform vec3 lightdir ;//= vec3(-0.707,-0.707,0);
uniform vec3 col;
varying vec2 varyingTextureCoordinate;
varying vec3 realcol;

//out vec4 fragColor;
varying vec3 normals;
float rand( float x, float y ){return fract( sin( x + y*0.192837465 )*1928374.0*cos(t * 0.01) );}
void main()
{
    float color = rand(gl_FragCoord.x+t, gl_FragCoord.y+t);
    vec3 lightdir = vec3(-0.707,-0.707,0);
    float ndotl = -dot(normalize(normals),lightdir);
    gl_FragColor = vec4(.5,.5,.5, 0)*ndotl+vec4(col, 1);
}
