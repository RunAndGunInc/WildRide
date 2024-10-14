xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header {
 1;
 0;
 1;
}

Mesh {
 11;
 30.042248;-68.376199;-26.862734;,
 38.238068;-68.376214;27.970640;,
 -8.442968;-68.376228;53.174801;,
 -45.489296;-68.376221;13.918422;,
 -21.704086;-68.376206;-35.547478;,
 10.440208;44.598236;-24.280182;,
 25.091606;30.326138;22.168808;,
 -13.975555;42.559349;38.302956;,
 -21.428249;50.261753;20.589779;,
 -20.639759;54.792580;-14.006619;,
 1.476519;56.151844;4.943608;;

 15;
 3;0,6,1;,
 3;0,5,6;,
 3;1,7,2;,
 3;1,6,7;,
 3;2,8,3;,
 3;2,7,8;,
 3;3,9,4;,
 3;3,8,9;,
 3;4,5,0;,
 3;4,9,5;,
 3;5,10,6;,
 3;6,10,7;,
 3;7,10,8;,
 3;8,10,9;,
 3;9,10,5;;

 MeshMaterialList {
  1;
  1;
  0;;
  Material {
   0.254902;0.227451;0.109804;1.000000;;
   19.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  11;
  0.802381;0.299642;-0.516139;,
  0.717868;0.340557;0.607195;,
  -0.511391;0.228373;0.828448;,
  -0.953324;0.284124;0.102211;,
  -0.359155;0.228237;-0.904939;,
  0.475806;0.614501;-0.629283;,
  0.809045;0.539719;0.232703;,
  0.118011;0.597827;0.792891;,
  -0.671079;0.624367;0.399774;,
  -0.532170;0.743474;-0.405020;,
  0.281040;0.947494;0.152551;;

  15;
  3;0,6,1;,
  3;0,5,6;,
  3;1,7,2;,
  3;1,6,7;,
  3;2,8,3;,
  3;2,7,8;,
  3;3,9,4;,
  3;3,8,9;,
  3;4,5,0;,
  3;4,9,5;,
  3;5,10,6;,
  3;6,10,7;,
  3;7,10,8;,
  3;8,10,9;,
  3;9,10,5;;
 }
 MeshTextureCoords {
  11;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
