#include <visualizer/infectious_disease_app.h>

using disease::visualizer::InfectiousDiseaseApp;

void prepareSettings(InfectiousDiseaseApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(InfectiousDiseaseApp, ci::app::RendererGl, prepareSettings);
