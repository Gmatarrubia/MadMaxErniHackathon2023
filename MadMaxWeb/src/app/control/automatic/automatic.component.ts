import { Component } from '@angular/core';

import { CommunicationService } from '../../shared/communication.service';

@Component({
  selector: 'app-automatic',
  templateUrl: './automatic.component.html',
  styleUrls: ['./automatic.component.css']
})
export class AutomaticComponent {
  constructor(private communicationService: CommunicationService) { }

  onStart() {
    this.communicationService.getPrueba();
  }
}
