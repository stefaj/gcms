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

// application time variable
uniform lowp float t;

// input from the vertex shader, this is the orientated position of the vertex
varying highp vec4 posi;

// these are texture samples. the way textures are rendered are determined by the
// samplers
// basic texture sampler
uniform sampler2D texture;

// normal vector sampler
/* uniform sampler2D normaltexture; */ // currently disabled

// constants
//uniform vec3 lightdir ;//= vec3(-0.707,-0.707,0);

// colour of each pixel to be displayed
uniform vec3 col;

// texture coordinates inherited from  vertex shader
varying vec2 varyingTextureCoordinate;

// normal vector for each pixel inherit from the vertex shader
varying vec3 normals;

// random noise generation
float rand( float x, float y ){return fract( sin( x + y*0.192837465 )*1928374.0*cos(t * 0.01) );}

void main()
{
    // generate a random colour
    float color = rand(gl_FragCoord.x+t, gl_FragCoord.y+t);

    // use a default light direction this can be changed later
    /* may change later */
    vec3 lightdir = vec3(-0.707,-0.707,-0.707);

    // calculate -N*L (blinn)
    float ndotl = -dot(normalize(normals),lightdir)+0.5;

    // set texture value
    vec4 texturecol = texture2D(texture,varyingTextureCoordinate).rgba;

    // set the active colour with a ambiet colour
    gl_FragColor = texturecol*ndotl+vec4(col, 1);

}
