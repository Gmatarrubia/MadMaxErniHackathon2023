import { Component } from '@angular/core';

import { CommunicationService } from '../../shared/communication.service';

@Component({
  selector: 'app-manual',
  templateUrl: './manual.component.html',
  styleUrls: ['./manual.component.css']
})
export class ManualComponent {
  constructor(private communicationService: CommunicationService) { }

  onForward() {
    this.communicationService.getPrueba();
  }

  onBackward() {
    this.communicationService.getPrueba();
  }

  onRightTurn() {
    this.communicationService.getPrueba();
  }

  onLeftTurn() {
    this.communicationService.getPrueba();
  }
}
