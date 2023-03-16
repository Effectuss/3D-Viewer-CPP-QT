#include <gtest/gtest.h>

#include "../model/affine.h"
#include "../model/obj_data.h"

ObjData obj;
Affine affine;

TEST(OpenFile, Exception) {
  EXPECT_THROW(obj.OpenFile("./object/FAKE.obj"), ViewerException);
  EXPECT_THROW(obj.OpenFile("./model/affine.cc"), ViewerException);
}

TEST(OpenFile, CorrectFile1) {
  obj.OpenFile("./object/Cube.obj");
  EXPECT_EQ(obj.GetModel(), "Cube.obj");
  affine.SetVertices(obj.GetVertices());
  EXPECT_EQ(affine.GetVertices().size(), 8);
  EXPECT_EQ(obj.GetFacets().size(), 36);
  EXPECT_DOUBLE_EQ(affine.GetVertices()[0].GetX(), 1.745441);
  EXPECT_DOUBLE_EQ(affine.GetVertices()[0].GetY(), 1.745441);
  EXPECT_DOUBLE_EQ(affine.GetVertices()[0].GetZ(), -1.745441);
  EXPECT_EQ(obj.GetFacets()[0].GetA(), 4);
  EXPECT_EQ(obj.GetFacets()[0].GetB(), 2);
  EXPECT_EQ(obj.GetFacets()[1].GetA(), 2);
  EXPECT_EQ(obj.GetFacets()[1].GetB(), 0);
  EXPECT_EQ(obj.GetFacets()[2].GetA(), 0);
  EXPECT_EQ(obj.GetFacets()[2].GetB(), 4);
  EXPECT_DOUBLE_EQ(obj.GetBorders().z_max, 1.745441);
  EXPECT_DOUBLE_EQ(obj.GetBorders().z_min, -1.745441);
}

TEST(OpenFile, CorrectFile2) {
  obj.OpenFile("./object/simple_cube.obj");
  EXPECT_EQ(obj.GetModel(), "simple_cube.obj");
  affine.SetVertices(obj.GetVertices());
  EXPECT_EQ(affine.GetVertices().size(), 8);
  EXPECT_EQ(obj.GetFacets().size(), 72);
  EXPECT_DOUBLE_EQ(affine.GetVertices()[0].GetX(), -0.5);
  EXPECT_DOUBLE_EQ(affine.GetVertices()[0].GetY(), -0.5);
  EXPECT_DOUBLE_EQ(affine.GetVertices()[0].GetZ(), -0.5);
  EXPECT_EQ(obj.GetFacets()[0].GetA(), 0);
  EXPECT_EQ(obj.GetFacets()[0].GetB(), 1);
  EXPECT_EQ(obj.GetFacets()[1].GetA(), 1);
  EXPECT_EQ(obj.GetFacets()[1].GetB(), 2);
  EXPECT_EQ(obj.GetFacets()[2].GetA(), 2);
  EXPECT_EQ(obj.GetFacets()[2].GetB(), 0);
  EXPECT_EQ(obj.GetFacets()[3].GetA(), 2);
  EXPECT_EQ(obj.GetFacets()[3].GetB(), 1);
  EXPECT_DOUBLE_EQ(obj.GetBorders().z_max, 0.5);
  EXPECT_DOUBLE_EQ(obj.GetBorders().z_min, -0.5);
}

TEST(Move, CorrectFile1) {
  obj.OpenFile("./object/Cube.obj");
  affine.SetVertices(obj.GetVertices());
  affine.MoveX(-2.0);
  affine.MoveY(-3.0);
  affine.MoveZ(4.0);
  EXPECT_NEAR(affine.GetVertices()[0].GetX(), -0.254559, 1e-6);
  EXPECT_NEAR(affine.GetVertices()[0].GetY(), -1.254559, 1e-6);
  EXPECT_NEAR(affine.GetVertices()[0].GetZ(), 2.254559, 1e-6);
  EXPECT_NEAR(affine.GetVertices()[6].GetX(), -3.745441, 1e-6);
  EXPECT_NEAR(affine.GetVertices()[6].GetY(), -1.25456, 1e-6);
  EXPECT_NEAR(affine.GetVertices()[6].GetZ(), 5.74544, 1e-6);
}

TEST(Move, CorrectFile2) {
  obj.OpenFile("./object/simple_cube.obj");
  affine.SetVertices(obj.GetVertices());
  affine.MoveX(-3.0);
  affine.MoveY(-1.0);
  affine.MoveZ(5.0);
  EXPECT_NEAR(affine.GetVertices()[0].GetX(), -3.5, 1e-6);
  EXPECT_NEAR(affine.GetVertices()[0].GetY(), -1.5, 1e-6);
  EXPECT_NEAR(affine.GetVertices()[0].GetZ(), 4.5, 1e-6);
  EXPECT_NEAR(affine.GetVertices()[6].GetX(), -2.5, 1e-6);
  EXPECT_NEAR(affine.GetVertices()[6].GetY(), -0.5, 1e-6);
  EXPECT_NEAR(affine.GetVertices()[6].GetZ(), 4.5, 1e-6);
}

TEST(Rotate, CorrectFile1) {
  obj.OpenFile("./object/Cube.obj");
  affine.SetVertices(obj.GetVertices());
  affine.RotateX(-2.0);
  affine.RotateY(-3.0);
  affine.RotateZ(4.0);
  EXPECT_NEAR(affine.GetVertices()[0].GetX(), -0.700771, 1e-6);
  EXPECT_NEAR(affine.GetVertices()[0].GetY(), 2.727999, 1e-6);
  EXPECT_NEAR(affine.GetVertices()[0].GetZ(), 1.098467, 1e-6);
  EXPECT_NEAR(affine.GetVertices()[6].GetX(), -0.69145, 1e-6);
  EXPECT_NEAR(affine.GetVertices()[6].GetY(), -2.117448, 1e-6);
  EXPECT_NEAR(affine.GetVertices()[6].GetZ(), 2.044015, 1e-6);
}

TEST(Rotate, CorrectFile2) {
  obj.OpenFile("./object/simple_cube.obj");
  affine.SetVertices(obj.GetVertices());
  affine.RotateX(-1.0);
  affine.RotateY(-2.0);
  affine.RotateZ(2.0);
  EXPECT_NEAR(affine.GetVertices()[0].GetX(), 0.598614, 1e-6);
  EXPECT_NEAR(affine.GetVertices()[0].GetY(), 0.352204, 1e-6);
  EXPECT_NEAR(affine.GetVertices()[0].GetZ(), -0.517314, 1e-6);
  EXPECT_NEAR(affine.GetVertices()[6].GetX(), -0.0379173, 1e-6);
  EXPECT_NEAR(affine.GetVertices()[6].GetY(), 0.444705, 1e-6);
  EXPECT_NEAR(affine.GetVertices()[6].GetZ(), 0.742159, 1e-6);
}

TEST(Scale, CorrectFile1) {
  obj.OpenFile("./object/Cube.obj");
  affine.SetVertices(obj.GetVertices());
  affine.Scale(2.0);
  EXPECT_NEAR(affine.GetVertices()[0].GetX(), 3.490882, 1e-6);
  EXPECT_NEAR(affine.GetVertices()[0].GetY(), 3.490882, 1e-6);
  EXPECT_NEAR(affine.GetVertices()[0].GetZ(), -3.490882, 1e-6);
  EXPECT_NEAR(affine.GetVertices()[4].GetX(), -3.490882, 1e-6);
  EXPECT_NEAR(affine.GetVertices()[4].GetY(), 3.490882, 1e-6);
  EXPECT_NEAR(affine.GetVertices()[4].GetZ(), -3.490882, 1e-6);
}

TEST(Scale, CorrectFile2) {
  obj.OpenFile("./object/simple_cube.obj");
  affine.SetVertices(obj.GetVertices());
  affine.Scale(3.0);
  EXPECT_NEAR(affine.GetVertices()[0].GetX(), -1.5, 1e-6);
  EXPECT_NEAR(affine.GetVertices()[0].GetY(), -1.5, 1e-6);
  EXPECT_NEAR(affine.GetVertices()[0].GetZ(), -1.5, 1e-6);
  EXPECT_NEAR(affine.GetVertices()[4].GetX(), 1.5, 1e-6);
  EXPECT_NEAR(affine.GetVertices()[4].GetY(), -1.5, 1e-6);
  EXPECT_NEAR(affine.GetVertices()[4].GetZ(), -1.5, 1e-6);
}

TEST(Memento, Save) {
  obj.OpenFile("./object/simple_cube.obj");
  affine.SetVertices(obj.GetVertices());
  double old_x = affine.GetVertices()[0].GetX();
  CareTaker caretaker(&affine);
  caretaker.Save();
  affine.Scale(2);
  caretaker.Undo();
  EXPECT_NEAR(affine.GetVertices()[0].GetX(), old_x, 1e-6);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
