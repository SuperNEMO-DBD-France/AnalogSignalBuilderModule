// snemo/asb/calo_signal_generator_driver.h
//
// Copyright (c) 2016-2018 F. Mauger <mauger@lpccaen.in2p3.fr>
//                         G. Oliviéro <goliviero@lpccaen.in2p3.fr>
//
// This file is part of Falaise/ASB plugin.
//
// Falaise/ASB plugin is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Falaise/ASB plugin is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Falaise/ASB plugin.  If not, see <http://www.gnu.org/licenses/>.

#ifndef FALAISE_ASB_PLUGIN_SNEMO_ASB_CALO_SIGNAL_GENERATOR_DRIVER_H
#define FALAISE_ASB_PLUGIN_SNEMO_ASB_CALO_SIGNAL_GENERATOR_DRIVER_H

// Standard library:
#include <string>
#include <memory>

// Third party:
// - Boost:
#include <boost/noncopyable.hpp>

// This project:
#include <snemo/asb/base_signal_generator_driver.h>

namespace snemo {

  namespace asb {

    /// \brief Calorimeter signal generator driver
    class calo_signal_generator_driver
      : public base_signal_generator_driver
      , private boost::noncopyable
    {
    public:

      /// \brief Driver model
      enum model_type {
        MODEL_INVALID  = 0, ///< Invalid model
        MODEL_TRIANGLE = 1  ///< Simplified model with triangular shape signals
        // MODEL_XXX = 2,   ///< XXX model with realistic shape signals
      };

      /// Constructor
      calo_signal_generator_driver(const std::string & id_ = "");

      /// Constructor
      calo_signal_generator_driver(const model_type model_,
                                   const std::string & id_ = "");

      /// Destructor
      virtual ~calo_signal_generator_driver();

      /// Set the driver model
      void set_model(const model_type);

      /// Return the driver model
      model_type get_model() const;

      /// Set the rise time
      void set_rise_time(const double rise_time_);

      double get_rise_time() const;

      /// Set the fall time
      void set_fall_time(const double fall_time_);

      double get_fall_time() const;

      /// Set the energy/amplitude conversion factor
      void set_energy_amplitude_factor(const double factor_);

      /// Return the energy/amplitude conversion factor
      double get_energy_amplitude_factor() const;

    protected :

      /// Initialize the algorithm through configuration properties
      virtual void _initialize(const datatools::properties & config_);

      /// Reset the algorithm
      virtual void _reset();

      /// Convert the calo energy hit into amplitude
      double _convert_energy_to_amplitude(const double energy_);

      /// Run the algorithm
      void _process(const mctools::simulated_data & sim_data_,
                    mctools::signal::signal_data & sim_signal_data_);

      // Smart print
      void _tree_dump(std::ostream & out_ = std::clog,
                      const std::string & indent_ = "") const;

    private:

      void _set_defaults_();

      /// Run the triangle model process
      void _process_triangle_model_(const mctools::simulated_data & sim_data_,
                                   mctools::signal::signal_data & sim_signal_data_);

    private:

      model_type _model_ = MODEL_INVALID; //!< Model type for PMT signals
      double _rise_time_;                 //!< Characteristic rise time for PMT signals
      double _fall_time_;                 //!< Characteristic fall time for PMT signals
      double _energy_amplitude_factor_;   //!< Energy-signal amplitude conversion factor

			// Macro to automate the registration of the driver :
			SNEMO_ASB_SIGNAL_GENERATOR_DRIVER_REGISTRATION_INTERFACE(calo_signal_generator_driver)

    };

  } // end of namespace asb

} // end of namespace snemo

#include <datatools/ocd_macros.h>

// Declare the OCD interface of the module
DOCD_CLASS_DECLARATION(snemo::asb::calo_signal_generator_driver)

#endif // FALAISE_ASB_PLUGIN_SNEMO_ASB_CALO_SIGNAL_GENERATOR_DRIVER_H

// Local Variables: --
// mode: c++ --
// c-file-style: "gnu" --
// tab-width: 2 --
// End: --
