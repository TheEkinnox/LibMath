#include <Matrix.h>
#include <Vector/Vector3.h>
#include <Angle/Radian.h>

#define GLM_FORCE_XYZW_ONLY
#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

using namespace LibMath::Literal;

#define CHECK_MATRIX(matrix, matrixGlm) \
	for (LibMath::Matrix::length_t i = 0; i < (matrix).getRowCount(); i++) \
		for(LibMath::Matrix::length_t j = 0; j < (matrix).getColumnCount(); j++) \
			CHECK((matrix)[(matrix).getIndex(i, j)] == Catch::Approx((matrixGlm)[i][j]))

TEST_CASE("Matrix3", "[.all][matrix][Matrix3]")
{
	SECTION("Instantiation")
	{
		// default constructor
		LibMath::Matrix3x3 empty;
		glm::mat3 emptyGlm{};
		CHECK_MATRIX(empty, emptyGlm);

		// destructor
		{
			LibMath::Matrix3 temp;
		}

		// basic constructor
		LibMath::Matrix3 oneParam{ 2.5f };
		glm::mat3 oneParamGlm = glm::mat3{ 2.5f };
		CHECK_MATRIX(oneParam, oneParamGlm);

		// copy constructor
		LibMath::Matrix3 copy{ oneParam };
		glm::mat3 copyGlm{ oneParamGlm };
		CHECK_MATRIX(copy, copyGlm);

		// assignment operator
		empty = oneParam;
		emptyGlm = oneParamGlm;
		CHECK_MATRIX(empty, emptyGlm);
	}

	//SECTION("Accessor")
	//{
	//	float const x = 2.5f;
	//	float const y = .5f;
	//	float const z = 2.f;
	//	LibMath::Matrix3 matrix{ x, y, z };

	//	{
	//		LibMath::Matrix3 const& matrixConst = matrix;
	//		CHECK(matrixConst[0] == x);
	//		CHECK(matrixConst[1] == y);
	//		CHECK(matrixConst[2] == z);
	//	}

	//	{
	//		matrix[0] += 1.f;
	//		matrix[1] += 1.f;
	//		matrix[2] += 1.f;
	//		CHECK(matrix[0] == x + 1.f);
	//		CHECK(matrix[1] == y + 1.f);
	//		CHECK(matrix[2] == z + 1.f);
	//	}
	//}

	SECTION("Comparator")
	{
		// compare with self
		LibMath::Matrix3 self;
		self[self.getIndex(0, 0)] = 2.5f;
		self[self.getIndex(0, 1)] = .5f;
		self[self.getIndex(0, 2)] = 2.f;
		self[self.getIndex(1, 0)] = 1.5f;
		self[self.getIndex(1, 1)] = -.5f;
		self[self.getIndex(1, 2)] = 1.f;
		self[self.getIndex(2, 0)] = 3.5f;
		self[self.getIndex(2, 1)] = 1.5f;
		self[self.getIndex(2, 2)] = 3.f;

		CHECK(self == self);

		// compare with same
		LibMath::Matrix3 same;
		same[same.getIndex(0, 0)] = 2.5f;
		same[same.getIndex(0, 1)] = .5f;
		same[same.getIndex(0, 2)] = 2.f;
		same[same.getIndex(1, 0)] = 1.5f;
		same[same.getIndex(1, 1)] = -.5f;
		same[same.getIndex(1, 2)] = 1.f;
		same[same.getIndex(2, 0)] = 3.5f;
		same[same.getIndex(2, 1)] = 1.5f;
		same[same.getIndex(2, 2)] = 3.f;

		CHECK(self == same);

		CHECK_FALSE(self.isIdentity());
		CHECK(LibMath::Matrix3{ 1.f }.isIdentity());
	}

	//SECTION("Constant")
	//{
	//	CHECK_MATRIX(LibMath::Matrix3::back(), glm::mat3(0.f, 0.f, -1.f));

	//	CHECK_MATRIX(LibMath::Matrix3::down(), glm::mat3(0.f, -1.f, 0.f));

	//	CHECK_MATRIX(LibMath::Matrix3::front(), glm::mat3(0.f, 0.f, 1.f));

	//	CHECK_MATRIX(LibMath::Matrix3::left(), glm::mat3(-1.f, 0.f, 0.f));

	//	CHECK_MATRIX(LibMath::Matrix3::one(), glm::mat3(1.f, 1.f, 1.f));

	//	CHECK_MATRIX(LibMath::Matrix3::right(), glm::mat3(1.f, 0.f, 0.f));

	//	CHECK_MATRIX(LibMath::Matrix3::up(), glm::mat3(0.f, 1.f, 0.f));

	//	CHECK_MATRIX(LibMath::Matrix3::zero(), glm::mat3(0.f, 0.f, 0.f));
	//}

	SECTION("Arithmetic")
	{
		LibMath::Matrix3 big;
		big[big.getIndex(0, 0)] = 3.75f;
		big[big.getIndex(0, 1)] = 3.f;
		big[big.getIndex(0, 2)] = .75f;
		big[big.getIndex(1, 0)] = 4.5f;
		big[big.getIndex(1, 1)] = 2.5f;
		big[big.getIndex(1, 2)] = 4.f;
		big[big.getIndex(2, 0)] = 6.5f;
		big[big.getIndex(2, 1)] = 4.5f;
		big[big.getIndex(2, 2)] = 6.f;

		LibMath::Matrix3 small;
		small[small.getIndex(0, 0)] = 2.5f;
		small[small.getIndex(0, 1)] = .5f;
		small[small.getIndex(0, 2)] = 2.f;
		small[small.getIndex(1, 0)] = 1.5f;
		small[small.getIndex(1, 1)] = -.5f;
		small[small.getIndex(1, 2)] = 1.f;
		small[small.getIndex(2, 0)] = 3.5f;
		small[small.getIndex(2, 1)] = 1.5f;
		small[small.getIndex(2, 2)] = 3.f;

		glm::mat3 bigGlm{};
		bigGlm[0][0] = 3.75f;
		bigGlm[0][1] = 3.f;
		bigGlm[0][2] = .75f;
		bigGlm[1][0] = 4.5f;
		bigGlm[1][1] = 2.5f;
		bigGlm[1][2] = 4.f;
		bigGlm[2][0] = 6.5f;
		bigGlm[2][1] = 4.5f;
		bigGlm[2][2] = 6.f;

		glm::mat3 smallGlm{};
		smallGlm[0][0] = 2.5f;
		smallGlm[0][1] = .5f;
		smallGlm[0][2] = 2.f;
		smallGlm[1][0] = 1.5f;
		smallGlm[1][1] = -.5f;
		smallGlm[1][2] = 1.f;
		smallGlm[2][0] = 3.5f;
		smallGlm[2][1] = 1.5f;
		smallGlm[2][2] = 3.f;

		SECTION("Addition")
		{
			{
				LibMath::Matrix3 sumAssignment = big;
				sumAssignment += small;

				glm::mat3 sumAssignmentGlm = bigGlm;
				sumAssignmentGlm += smallGlm;

				CHECK_MATRIX(sumAssignment, sumAssignmentGlm);
			}

			{
				LibMath::Matrix3 sum = big + small;

				glm::mat3 sumGlm = bigGlm + smallGlm;

				CHECK_MATRIX(sum, sumGlm);
			}

			{
				LibMath::Matrix3 sumScalarAssignment = small;
				sumScalarAssignment += 2.64f;

				glm::mat3 sumScalarAssignmentGlm = smallGlm;
				sumScalarAssignmentGlm += 2.64f;

				CHECK_MATRIX(sumScalarAssignment, sumScalarAssignmentGlm);
			}

			{
				LibMath::Matrix3 sumScalar = small + 2.64f;

				glm::mat3 sumScalarGlm = smallGlm + 2.64f;

				CHECK_MATRIX(sumScalar, sumScalarGlm);
			}
		}

		SECTION("Subtraction")
		{
			{
				LibMath::Matrix3 differenceAssignment = big;
				differenceAssignment -= small;

				glm::mat3 differenceAssignmentGlm = bigGlm;
				differenceAssignmentGlm -= smallGlm;

				CHECK_MATRIX(differenceAssignment, differenceAssignmentGlm);
			}

			{
				LibMath::Matrix3 difference = big - small;

				glm::mat3 differenceGlm = bigGlm - smallGlm;

				CHECK_MATRIX(difference, differenceGlm);
			}

			{
				LibMath::Matrix3 differenceScalarAssignment = small;
				differenceScalarAssignment -= 2.64f;

				glm::mat3 differenceScalarAssignmentGlm = smallGlm;
				differenceScalarAssignmentGlm -= 2.64f;

				CHECK_MATRIX(differenceScalarAssignment, differenceScalarAssignmentGlm);
			}

			{
				LibMath::Matrix3 differenceScalar = small - 2.64f;

				glm::mat3 differenceScalarGlm = smallGlm - 2.64f;

				CHECK_MATRIX(differenceScalar, differenceScalarGlm);
			}
		}

		SECTION("Multiplication")
		{
			{
				LibMath::Matrix3 productAssignment = big;
				productAssignment *= small;

				// Transpose since glm matrices are column major unlike ours
				glm::mat3 productAssignmentGlm = glm::transpose(bigGlm);
				productAssignmentGlm *= glm::transpose(smallGlm);

				CHECK_MATRIX(productAssignment, glm::transpose(productAssignmentGlm));
			}

			{
				LibMath::Matrix3 product = big * small;

				// Transpose since glm matrices are column major unlike ours
				glm::mat3 productGlm = glm::transpose(bigGlm) * glm::transpose(smallGlm);

				CHECK_MATRIX(product, glm::transpose(productGlm));
			}

			{
				LibMath::Matrix3 productScalarAssignment = small;
				productScalarAssignment *= 2.64f;

				glm::mat3 productScalarAssignmentGlm = smallGlm;
				productScalarAssignmentGlm *= 2.64f;

				CHECK_MATRIX(productScalarAssignment, productScalarAssignmentGlm);
			}

			{
				LibMath::Matrix3 productScalar = small * 2.64f;

				glm::mat3 productScalarGlm = smallGlm * 2.64f;

				CHECK_MATRIX(productScalar, productScalarGlm);
			}
		}

		SECTION("Division")
		{
			{
				LibMath::Matrix3 quotientAssignment = small;
				quotientAssignment /= big;

				// Todo: rework test to account for glm matrices being column major unlike ours
				glm::mat3 quotientAssignmentGlm = glm::transpose(smallGlm);
				quotientAssignmentGlm /= glm::transpose(bigGlm);

				CHECK_MATRIX(quotientAssignment, glm::transpose(quotientAssignmentGlm));
			}

			{
				LibMath::Matrix3 quotient = small / big;

				// Todo: rework test to account for glm matrices being column major unlike ours
				glm::mat3 quotientGlm = glm::transpose(smallGlm) / glm::transpose(bigGlm);

				CHECK_MATRIX(quotient, glm::transpose(quotientGlm));
			}

			{
				LibMath::Matrix3 quotientScalarAssignment = small;
				quotientScalarAssignment /= 2.64f;

				glm::mat3 quotientScalarAssignmentGlm = smallGlm;
				quotientScalarAssignmentGlm /= 2.64f;

				CHECK_MATRIX(quotientScalarAssignment, quotientScalarAssignmentGlm);
			}

			{
				LibMath::Matrix3 quotientScalar = small / 2.64f;

				glm::mat3 quotientScalarGlm = smallGlm / 2.64f;

				CHECK_MATRIX(quotientScalar, quotientScalarGlm);
			}
		}

		SECTION("Negative")
		{
			LibMath::Matrix3 negative = -big;

			glm::mat3 negativeGlm = -bigGlm;

			CHECK_MATRIX(negative, negativeGlm);
		}
	}

	SECTION("Functionality")
	{
		LibMath::Matrix3 big;
		big[big.getIndex(0, 0)] = 3.75f;
		big[big.getIndex(0, 1)] = 3.f;
		big[big.getIndex(0, 2)] = .75f;
		big[big.getIndex(1, 0)] = 4.5f;
		big[big.getIndex(1, 1)] = 2.5f;
		big[big.getIndex(1, 2)] = 4.f;
		big[big.getIndex(2, 0)] = 6.5f;
		big[big.getIndex(2, 1)] = 4.5f;
		big[big.getIndex(2, 2)] = 6.f;

		LibMath::Matrix3 small;
		small[small.getIndex(0, 0)] = 2.5f;
		small[small.getIndex(0, 1)] = .5f;
		small[small.getIndex(0, 2)] = 2.f;
		small[small.getIndex(1, 0)] = 1.5f;
		small[small.getIndex(1, 1)] = -.5f;
		small[small.getIndex(1, 2)] = 1.f;
		small[small.getIndex(2, 0)] = 3.5f;
		small[small.getIndex(2, 1)] = 1.5f;
		small[small.getIndex(2, 2)] = 3.f;

		glm::mat3 bigGlm{};
		bigGlm[0][0] = 3.75f;
		bigGlm[0][1] = 3.f;
		bigGlm[0][2] = .75f;
		bigGlm[1][0] = 4.5f;
		bigGlm[1][1] = 2.5f;
		bigGlm[1][2] = 4.f;
		bigGlm[2][0] = 6.5f;
		bigGlm[2][1] = 4.5f;
		bigGlm[2][2] = 6.f;

		glm::mat3 smallGlm{};
		smallGlm[0][0] = 2.5f;
		smallGlm[0][1] = .5f;
		smallGlm[0][2] = 2.f;
		smallGlm[1][0] = 1.5f;
		smallGlm[1][1] = -.5f;
		smallGlm[1][2] = 1.f;
		smallGlm[2][0] = 3.5f;
		smallGlm[2][1] = 1.5f;
		smallGlm[2][2] = 3.f;

		SECTION("Determinant")
		{
			float determinant = big.determinant();

			float determinantGlm = glm::determinant(bigGlm);

			CHECK(determinant == Catch::Approx(determinantGlm));
		}

		SECTION("Cofactor")
		{
			// Todo: rework test to account for glm matrices being column major unlike ours
			glm::mat3 cofactorMatGlm = glm::transpose(glm::inverse(bigGlm) * glm::determinant(bigGlm));

			for (LibMath::Matrix::length_t row = 0; row < big.getRowCount(); row++)
			{
				for (LibMath::Matrix::length_t col = 0; col < big.getColumnCount(); col++)
				{
					float cofactor = big.cofactor(row, col);

					float cofactorGlm = cofactorMatGlm[row][col];

					CHECK(cofactor == Catch::Approx(cofactorGlm));
				}
			}
		}

		SECTION("CofactorMatrix")
		{
			// Small should not have a cofactor matrix (non-invertible)
			CHECK_THROWS(small.coMatrix());

			LibMath::Matrix3 cofactorMat = big.coMatrix();
			glm::mat3 cofactorMatGlm = glm::transpose(glm::inverse(bigGlm) * glm::determinant(bigGlm));
			
			CHECK_MATRIX(cofactorMat, cofactorMatGlm);
		}

		SECTION("Inverse")
		{
			// Small should be non-invertible
			CHECK_THROWS(small.inverse());

			LibMath::Matrix3 inverse = big.inverse();

			// Todo: rework test to account for glm matrices being column major unlike ours
			glm::mat3 inverseGlm = glm::inverse(glm::transpose(bigGlm));

			CHECK_MATRIX(inverse, glm::transpose(inverseGlm));
		}
	}

	//SECTION("Extra")
	//{
	//	LibMath::Matrix3 const input{ 2.5f, -.5f, 2.f };
	//	{
	//		std::stringstream buffer;
	//		buffer << input;
	//		CHECK(buffer.str() == "{2.5,-0.5,2}");

	//		buffer << " extra";

	//		LibMath::Matrix3 output;
	//		buffer >> output;
	//		CHECK(output == input);

	//		std::string extra;
	//		buffer >> extra;
	//		CHECK(extra == "extra");
	//	}

	//	{
	//		CHECK(input.string() == "{2.5,-0.5,2}");

	//		CHECK(input.stringLong() == "Matrix3{ x:2.5, y:-0.5, z:2 }");
	//	}
	//}

	SECTION("Debug")
	{
#if (defined _DEBUG) || (! defined NDEBUG)
		LibMath::Matrix3 matrix{};

		CHECK_THROWS(matrix[matrix.getIndex(-1, 0)]);
		CHECK_THROWS(matrix[matrix.getIndex(0, -1)]);
		CHECK_THROWS(matrix[matrix.getIndex(-1, -1)]);
		CHECK_THROWS(matrix[matrix.getIndex(3, 0)]);
		CHECK_THROWS(matrix[matrix.getIndex(0, 3)]);
		CHECK_THROWS(matrix[matrix.getIndex(3, 3)]);
		CHECK_THROWS(matrix[9]);
#endif // DEBUG
	}
}

TEST_CASE("Matrix4", "[.all][matrix][Matrix4]")
{
	SECTION("Transformation")
	{
		LibMath::Vector3 const transformation{ -2.f, 0.f, 1.25f };

		glm::vec3 const transformationGlm{ -2.f, 0.f, 1.25f };

		SECTION("Translation")
		{
			LibMath::Matrix4 translate = LibMath::Matrix4::translation(transformation.m_x, transformation.m_y, transformation.m_z);

			glm::mat4 translateGlm = glm::translate(transformationGlm);

			// Transpose since glm matrices are column major unlike ours
			CHECK_MATRIX(translate, glm::transpose(translateGlm));
		}

		SECTION("Scale")
		{
			LibMath::Matrix4 scale = LibMath::Matrix4::scaling(transformation.m_x, transformation.m_y, transformation.m_z);

			glm::mat4 scaleGlm = glm::scale(transformationGlm);

			// Transpose since glm matrices are column major unlike ours
			CHECK_MATRIX(scale, glm::transpose(scaleGlm));
		}

		SECTION("Rotation")
		{
			SECTION("Axis")
			{
				LibMath::Matrix4 rotate = LibMath::Matrix4::rotation(-3_rad, transformation);
				glm::mat4 rotateGlm = glm::rotate(-3.f, transformationGlm);

				// Transpose since glm matrices are column major unlike ours
				CHECK_MATRIX(rotate, glm::transpose(rotateGlm));
			}

			SECTION("Euler Angle")
			{
				LibMath::Matrix4 rotate = LibMath::Matrix4::rotationEuler(LibMath::Radian{ transformation.m_x }, LibMath::Radian{ transformation.m_y }, LibMath::Radian{ transformation.m_z });

				glm::mat4 rotateGlm = glm::orientate4(transformationGlm);

				// Transpose since glm matrices are column major unlike ours
				CHECK_MATRIX(rotate, glm::transpose(rotateGlm));
			}
		}
	}
}
