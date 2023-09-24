import { Component } from '@angular/core';

import { CommunicationService } from '../shared/communication.service';

@Component({
  selector: 'app-control',
  templateUrl: './control.component.html',
  styleUrls: ['./control.component.css']
})
export class ControlComponent {

  constructor (private communicationService: CommunicationService) {}

  onAutomatic() {
    this.communicationService.setControlType(0);
  }

  onManual() {
    this.communicationService.setControlType(1);
  }
}
