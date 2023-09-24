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
  isStarted: boolean = false;

  constructor(private communicationService: CommunicationService) { }

  ngOnInit() {
    // const firebasePath = 'automatic';
    // this.communicationService.getData(firebasePath).subscribe((data) => {
    //   this.firebaseData = data;
    // })
  }

  onStart() {
    this.communicationService.setAutomatic(new Automatic(1));
    this.communicationService.setStatus(new Status("Started", 15, 5)); // Comment out!
    this.isStarted = true;
  }

  onPause() {
    this.communicationService.setAutomatic(new Automatic(2));
    this.communicationService.setStatus(new Status("Paused", 0, 5)); // Comment out!
    this.isStarted = false;
  }

  onStop() {
    this.communicationService.setAutomatic(new Automatic(0));
    this.communicationService.setStatus(new Status("Stopped", 0, 1)); // Comment out!
    this.isStarted = false;
  }
}
