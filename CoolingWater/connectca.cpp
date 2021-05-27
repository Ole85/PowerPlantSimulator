#include <compressedair.h>

void CompressedAir::fconnect() {
  connect(controlPanelCA, &ControlPanelCA::signalButtonName, this,
          &CompressedAir::slotButtonClick);
  connect(controlPanelCA, &ControlPanelCA::signalPriorityCompressor, this,
          &CompressedAir::slotPriorityChange);
  connect(controlPanelCA, &ControlPanelCA::signalCvPSH, this,
          &CompressedAir::slotSpinBoxPSH);
  connect(controlPanelCA, &ControlPanelCA::signalCvPSL, this,
          &CompressedAir::slotSpinBoxPSL);
  connect(controlPanelCA, &ControlPanelCA::signalCvPSLL, this,
          &CompressedAir::slotSpinBoxPSLL);
#if !LIBMODE
  connect(clockTimer, &QTimer::timeout, this, &CompressedAir::slotCycle);
#endif
  connect(blinkingTimer, &QTimer::timeout, this,
          &CompressedAir::slotLightUpStatus);
  connect(controlPanelCA, &ControlPanelCA::signalOperationMode, this,
          &CompressedAir::slotOperationMode);
}
