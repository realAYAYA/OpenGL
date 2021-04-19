#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices=18) out;

uniform mat4 shadowMatrices[6];

out vec4 FragPos; // FragPos from GS (output per emitvertex)

void main()
{
    for(int face = 0; face < 6; ++face)
    {
        gl_Layer = face; // built-in variable that specifies to which face we render.
        for(int i = 0; i < 3; ++i) // for each triangle's vertices
        {
            FragPos = gl_in[i].gl_Position;
            gl_Position = shadowMatrices[face] * FragPos;
            EmitVertex();
        }    
        EndPrimitive();
    }
}

/** About gl_Layer
|The geometry shader has a built-in variable called gl_Layer that specifies 
|which cubemap face to emit a primitive to. When left alone, the geometry shader 
|just sends its primitives further down the pipeline as usual, but when we update 
|this variable we can control to which cubemap face we render to for each primitive.
|This of course only works when we have a cubemap texture attached to the active framebuffer.
*/