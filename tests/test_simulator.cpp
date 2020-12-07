//
// Created by Megan Lov on 12/6/20.
//
#include "visualizer/simulator.h"

#include <catch2/catch.hpp>

using disease::visualizer::Simulator;

TEST_CASE("Check member variables update") {
  Simulator simulator;

  SECTION("Population has been created") {
    simulator.CreatePopulation();

    simulator.Update();

    REQUIRE(simulator.GetParticlesInfo().size() == 201);
    REQUIRE(simulator.GetTimePassed() == 1);
  }

  SECTION("Population has not been created") {
    simulator.Update();

    REQUIRE(simulator.GetParticlesInfo().size() == 0);
    REQUIRE(simulator.GetTimePassed() == 0);
  }
}

TEST_CASE("Check population gets created") {
  Simulator simulator;

  simulator.CreatePopulation();
  REQUIRE(simulator.GetDiseaseClass().GetPopulation().size() == 201);
}

TEST_CASE("Check feature values change") {
  Simulator simulator;

  SECTION("Check quarantine value changes") {
    simulator.ChangeFeature(disease::FeatureChangeKey::kQuarantine);
    REQUIRE(simulator.GetFeatureCurrentlyChanging() == disease::FeatureChangeKey::kQuarantine);
    REQUIRE(simulator.GetDiseaseClass().GetShouldQuarantineValue() == true);

    SECTION("With arrow up") {
      simulator.ChangeFeatureValue(true);
      REQUIRE(simulator.GetDiseaseClass().GetShouldQuarantineValue() == false);

      simulator.ChangeFeatureValue(true);
      REQUIRE(simulator.GetDiseaseClass().GetShouldQuarantineValue() == true);
    }

    SECTION("With arrow down") {
      simulator.ChangeFeatureValue(false);
      REQUIRE(simulator.GetDiseaseClass().GetShouldQuarantineValue() == false);

      simulator.ChangeFeatureValue(false);
      REQUIRE(simulator.GetDiseaseClass().GetShouldQuarantineValue() == true);
    }
  }

  SECTION("Check exposure time changes") {
    simulator.ChangeFeature(disease::FeatureChangeKey::kExposureTime);
    REQUIRE(simulator.GetFeatureCurrentlyChanging() == disease::FeatureChangeKey::kExposureTime);
    REQUIRE(simulator.GetDiseaseClass().GetExposureTime() == 25);

    SECTION("With arrow up") {
      simulator.ChangeFeatureValue(true);
      REQUIRE(simulator.GetDiseaseClass().GetExposureTime() == 30);  // original value + increment value
    }

    SECTION("With arrow down") {
      simulator.ChangeFeatureValue(false);
      REQUIRE(simulator.GetDiseaseClass().GetExposureTime() == 20);
    }

    SECTION("Exposure time is minimum before change") {
      while (simulator.GetDiseaseClass().GetExposureTime() > 5) {
        simulator.ChangeFeatureValue(false);
      }
      REQUIRE(simulator.GetDiseaseClass().GetExposureTime() == 5);

      SECTION("With arrow up") {
        simulator.ChangeFeatureValue(true);
        REQUIRE(simulator.GetDiseaseClass().GetExposureTime() == 10);
      }

      SECTION("With arrow down") {
        simulator.ChangeFeatureValue(false);
        REQUIRE(simulator.GetDiseaseClass().GetExposureTime() == 5);
      }
    }

    SECTION("Exposure time is maximum before change") {
      while (simulator.GetDiseaseClass().GetExposureTime() < 50) {
        simulator.ChangeFeatureValue(true);
      }
      REQUIRE(simulator.GetDiseaseClass().GetExposureTime() == 50);

      SECTION("With arrow up") {
        simulator.ChangeFeatureValue(true);
        REQUIRE(simulator.GetDiseaseClass().GetExposureTime() == 50);
      }

      SECTION("With arrow down") {
        simulator.ChangeFeatureValue(false);
        REQUIRE(simulator.GetDiseaseClass().GetExposureTime() == 45);
      }
    }
  }

  SECTION("Check infected time changes") {
    simulator.ChangeFeature(disease::FeatureChangeKey::kInfectedTime);
    REQUIRE(simulator.GetFeatureCurrentlyChanging() == disease::FeatureChangeKey::kInfectedTime);
    REQUIRE(simulator.GetDiseaseClass().GetInfectedTime() == 500);

    SECTION("With arrow up") {
      simulator.ChangeFeatureValue(true);
      REQUIRE(simulator.GetDiseaseClass().GetInfectedTime() == 505);
    }

    SECTION("With arrow down") {
      simulator.ChangeFeatureValue(false);
      REQUIRE(simulator.GetDiseaseClass().GetInfectedTime() == 495);
    }

    SECTION("Infected time is minimum before change") {
      while (simulator.GetDiseaseClass().GetInfectedTime() > 100) {
        simulator.ChangeFeatureValue(false);
      }
      REQUIRE(simulator.GetDiseaseClass().GetInfectedTime() == 100);

      SECTION("With arrow up") {
        simulator.ChangeFeatureValue(true);
        REQUIRE(simulator.GetDiseaseClass().GetInfectedTime() == 105);
      }

      SECTION("With arrow down") {
        simulator.ChangeFeatureValue(false);
        REQUIRE(simulator.GetDiseaseClass().GetInfectedTime() == 100);
      }
    }

    SECTION("Infected time is maximum before change") {
      while (simulator.GetDiseaseClass().GetInfectedTime() < 1000) {
        simulator.ChangeFeatureValue(true);
      }
      REQUIRE(simulator.GetDiseaseClass().GetInfectedTime() == 1000);

      SECTION("With arrow up") {
        simulator.ChangeFeatureValue(true);
        REQUIRE(simulator.GetDiseaseClass().GetInfectedTime() == 1000);
      }

      SECTION("With arrow down") {
        simulator.ChangeFeatureValue(false);
        REQUIRE(simulator.GetDiseaseClass().GetInfectedTime() == 995);
      }
    }
  }

  SECTION("Check social distance changes") {
    SECTION("With arrow up") {

    }

    SECTION("With arrow down") {

    }

    SECTION("Social distance is minimum before change") {
      SECTION("With arrow up") {

      }

      SECTION("With arrow down") {

      }
    }

    SECTION("Social distance is maximum before change") {
      SECTION("With arrow up") {

      }

      SECTION("With arrow down") {

      }
    }
  }

  SECTION("Check infection radius changes") {
    SECTION("With arrow up") {

    }

    SECTION("With arrow down") {

    }

    SECTION("Infection radius is minimum before change") {
      SECTION("With arrow up") {

      }

      SECTION("With arrow down") {

      }
    }

    SECTION("Infection radius is maximum before change") {
      SECTION("With arrow up") {

      }

      SECTION("With arrow down") {

      }
    }

    SECTION("Infection radius cannot be lower than social distance value") {

    }
  }
}

TEST_CASE("Check member variables clear") {

}

TEST_CASE("Check GetFeatureBeingChanged() works") {
  SECTION("Quarantine is feature being changed") {

  }

  SECTION("Exposed time is feature being changed") {

  }

  SECTION("Infected time is feature being changed") {

  }

  SECTION("Social distance is feature being changed") {

  }

  SECTION("Radius of infection is feature being changed") {

  }
}