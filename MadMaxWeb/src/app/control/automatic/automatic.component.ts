import { Component } from '@angular/core';

import { CommunicationService } from '../../shared/communication.service';
import { Automatic } from './automatic.model';

@Component({
  selector: 'app-automatic',
  templateUrl: './automatic.component.html',
  styleUrls: ['./automatic.component.css']
})
export class AutomaticComponent {
  constructor(private communicationService: CommunicationService) { }

  onStart() {
    this.communicationService.setAutomatic(new Automatic(true));
  }

  onStop() {
    this.communicationService.setAutomatic(new Automatic(false));
  }
}
