#include <gtest/gtest.h>
#include "../src/threeDShape.h"

TEST(SphereTest, VolumeCalculation) {
    Sphere sphere1(1); // Radius 1
    EXPECT_NEAR(4.18879, sphere1.volume(), 0.01);

    Sphere sphere2(3); // Radius 3
    EXPECT_NEAR(113.097, sphere2.volume(), 0.01);

    Sphere sphere3(5); // Radius 5
    EXPECT_NEAR(523.598, sphere3.volume(), 0.01);
}

// Sphere Surface Area Tests
TEST(SphereSurfaceAreaTest, Calculation) {
    Sphere smallSphere(1); // Radius 1
    EXPECT_NEAR(12.56, smallSphere.surfaceArea(), 0.01);

    Sphere mediumSphere(3); // Radius 3
    EXPECT_NEAR(113.097, mediumSphere.surfaceArea(), 0.01);

    Sphere largeSphere(5); // Radius 5
    EXPECT_NEAR(314.159, largeSphere.surfaceArea(), 0.01);
}

TEST(PyramidTest, VolumeCalculation) {
    Pyramid pyramid1(1, 1, 1); // Base Width 1, Base Length 1, Height 1
    EXPECT_NEAR(1.0 / 3.0, pyramid1.volume(), 0.01);

    Pyramid pyramid2(3, 4, 6); // Base Width 3, Base Length 4, Height 6
    EXPECT_NEAR(24, pyramid2.volume(), 0.01);

    Pyramid pyramid3(5, 5, 10); // Base Width 5, Base Length 5, Height 10
    EXPECT_NEAR(83.3333, pyramid3.volume(), 0.01);
}

// Pyramid Surface Area Tests
TEST(PyramidSurfaceAreaTest, Calculation) {
    // Small pyramid
    Pyramid smallPyramid(1, 1, 1); // Base Width 1, Base Length 1, Height 1
    double slantHeightWidthSmall = sqrt(pow(1 / 2.0, 2) + pow(1, 2));
    double slantHeightLengthSmall = sqrt(pow(1 / 2.0, 2) + pow(1, 2));
    double baseAreaSmall = 1 * 1;
    double lateralSurfaceAreaSmall = (1 * slantHeightWidthSmall / 2) * 2 +
                                     (1 * slantHeightLengthSmall / 2) * 2;
    double expectedSurfaceAreaSmall = baseAreaSmall + lateralSurfaceAreaSmall;

    EXPECT_NEAR(expectedSurfaceAreaSmall, smallPyramid.surfaceArea(), 0.01);

    // Medium pyramid
    Pyramid mediumPyramid(3, 4, 6); // Base Width 3, Base Length 4, Height 6
    double slantHeightWidth = sqrt(pow(3 / 2.0, 2) + pow(6, 2));
    double slantHeightLength = sqrt(pow(4 / 2.0, 2) + pow(6, 2));
    double baseArea = 3 * 4;
    double lateralSurfaceArea = (3 * slantHeightWidth / 2) * 2 +
                                (4 * slantHeightLength / 2) * 2;
    double expectedSurfaceArea = baseArea + lateralSurfaceArea;

    EXPECT_NEAR(expectedSurfaceArea, mediumPyramid.surfaceArea(), 0.01);

    // Large pyramid
    Pyramid largePyramid(10, 10, 10); // Base Width 10, Base Length 10, Height 10
    double slantHeightWidthLarge = sqrt(pow(10 / 2.0, 2) + pow(10, 2));
    double slantHeightLengthLarge = sqrt(pow(10 / 2.0, 2) + pow(10, 2));
    double baseAreaLarge = 10 * 10;
    double lateralSurfaceAreaLarge = (10 * slantHeightWidthLarge / 2) * 2 +
                                     (10 * slantHeightLengthLarge / 2) * 2;
    double expectedSurfaceAreaLarge = baseAreaLarge + lateralSurfaceAreaLarge;

    EXPECT_NEAR(expectedSurfaceAreaLarge, largePyramid.surfaceArea(), 0.01);
}

TEST(DynamicArrayTest, PolymorphicBehavior) {
    // Create a dynamic array of ThreeDShape pointers
    const int numShapes = 4;
    auto** shapes = new ThreeDShape*[numShapes];

    // Populate the array with different shapes
    shapes[0] = new Sphere(1); // Volume = 4/3 * π * 1^3
    shapes[1] = new Pyramid(1, 1, 3); // Volume = 1 * 1 * 3 / 3
    shapes[2] = new Sphere(2); // Volume = 4/3 * π * 2^3
    shapes[3] = new Pyramid(2, 2, 4); // Volume = 2 * 2 * 4 / 3

    // Check that each shape calculates the correct volume
    EXPECT_NEAR(4.18879, shapes[0]->volume(), 0.01);
    EXPECT_NEAR(1, shapes[1]->volume(), 0.01);
    EXPECT_NEAR(33.51032, shapes[2]->volume(), 0.01);
    EXPECT_NEAR(5.33333, shapes[3]->volume(), 0.01);

    // Cleanup
    for (int i = 0; i < numShapes; ++i) {
        delete shapes[i];
    }
    delete[] shapes;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
