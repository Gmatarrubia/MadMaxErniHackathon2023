import { Component, OnInit } from '@angular/core';

import { CommunicationService } from '../shared/communication.service';
import { Automatic } from '../control/automatic/automatic.model';

@Component({
  selector: 'app-status',
  templateUrl: './status.component.html',
  styleUrls: ['./status.component.css']
})
export class StatusComponent {

  statusFirebaseData: any;
  automaticFirebaseData: any;
  timer: number = 0;
  timerRef: any;

  constructor(private communicationService: CommunicationService) { }

  ngOnInit() {
    const firebasePath = 'status';
    this.communicationService.getData(firebasePath).subscribe((data) => {
      this.statusFirebaseData = data;
    })

    this.communicationService.getData('automatic').subscribe((data) => {
      this.automaticFirebaseData = data;
      if (data.move) {
        const startTime = Date.now() - (this.timer || 0);
        this.timerRef = setInterval(() => {
          this.timer = Date.now() - startTime;
        })
      } 
      else {
        this.timer = 0;
        clearInterval(this.timerRef);
      }
    })
  }
}
