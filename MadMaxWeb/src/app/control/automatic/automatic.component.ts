import { Component, OnInit } from '@angular/core';

import { CommunicationService } from '../../shared/communication.service';
import { Automatic } from './automatic.model';

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
  }

  onStop() {
    this.communicationService.setAutomatic(new Automatic(false));
  }
}
