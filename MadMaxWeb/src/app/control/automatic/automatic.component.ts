import { Component, OnInit } from '@angular/core';

import { CommunicationService } from '../../shared/communication.service';
import { Automatic } from './automatic.model';
import { Status } from '../../status/status.model';

@Component({
  selector: 'app-automatic',
  templateUrl: './automatic.component.html',
  styleUrls: ['./automatic.component.css']
})
export class AutomaticComponent {
  firebaseData: any;

  constructor(private communicationService: CommunicationService) { }

  ngOnInit() {
    const firebasePath = 'automatic';
    this.communicationService.getData(firebasePath).subscribe((data) => {
      this.firebaseData = data;
    })
  }

  onStart() {
    this.communicationService.setAutomatic(new Automatic(true));
    this.communicationService.setStatus(new Status("Started", 15, 5));
  }

  onStop() {
    this.communicationService.setAutomatic(new Automatic(false));
    this.communicationService.setStatus(new Status("Stopped", 0, 1));
  }
}
