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
 10;
 16.837492;53.392918;-1.432998;,
 14.991937;19.250183;-2.878408;,
 28.833588;-9.355894;-4.669732;,
 -32.069672;-9.355894;-4.669732;,
 -13.614141;24.786842;-2.596357;,
 16.837492;53.392914;1.204658;,
 14.991937;19.250175;2.650068;,
 28.833588;-9.355902;4.441391;,
 -32.069672;-9.355902;4.441391;,
 -13.614141;24.786835;2.368016;;

 16;
 3;1,4,0;,
 3;4,2,3;,
 3;4,1,2;,
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
 3;9,6,5;,
 3;7,9,8;,
 3;6,9,7;;

 MeshMaterialList {
  1;
  1;
  0;;
  Material {
   0.478431;0.478431;0.478431;1.000000;;
   15.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  30;
  -0.001647;0.042385;-0.999100;,
  0.998542;-0.053975;-0.000000;,
  -0.684675;0.728848;0.000001;,
  0.000421;0.053044;-0.998592;,
  0.998542;-0.053975;-0.000000;,
  0.900159;0.435561;0.000000;,
  0.001244;0.062156;-0.998066;,
  0.900159;0.435561;0.000000;,
  0.000000;-1.000000;-0.000001;,
  0.000000;0.060615;-0.998161;,
  0.000000;-1.000000;-0.000001;,
  -0.879707;0.475517;0.000000;,
  0.000280;0.055568;-0.998455;,
  -0.879707;0.475517;0.000000;,
  -0.684675;0.728848;0.000001;,
  0.998542;-0.053975;-0.000000;,
  -0.684675;0.728848;0.000001;,
  -0.001647;0.042385;0.999100;,
  0.998542;-0.053975;-0.000000;,
  0.900159;0.435561;0.000001;,
  0.000421;0.053044;0.998592;,
  0.900159;0.435561;0.000000;,
  -0.000000;-1.000000;-0.000001;,
  0.001244;0.062156;0.998066;,
  0.000000;-1.000000;-0.000001;,
  -0.879707;0.475517;0.000000;,
  0.000000;0.060615;0.998161;,
  -0.879707;0.475517;0.000000;,
  -0.684675;0.728848;0.000001;,
  0.000280;0.055568;0.998455;;

  16;
  3;3,12,0;,
  3;12,6,9;,
  3;12,3,6;,
  3;1,18,4;,
  3;1,15,18;,
  3;5,21,7;,
  3;5,19,21;,
  3;8,24,10;,
  3;8,22,24;,
  3;11,27,13;,
  3;11,25,27;,
  3;14,16,2;,
  3;14,28,16;,
  3;29,20,17;,
  3;23,29,26;,
  3;20,29,23;;
 }
 MeshTextureCoords {
  10;
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
