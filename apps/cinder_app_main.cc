#include <visualizer/infectious_disease_app.h>

using disease::visualizer::NaiveBayesApp;

void prepareSettings(NaiveBayesApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(NaiveBayesApp, ci::app::RendererGl, prepareSettings);
